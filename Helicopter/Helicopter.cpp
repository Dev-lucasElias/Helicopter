#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>
#include <windows.h>
#include <conio.h>
#include <string>

using namespace std;

// Definições
constexpr int SCREEN_WIDTH = 156;
constexpr int SCREEN_HEIGHT = 40;
constexpr int MAX_MISSILES = 20;
constexpr int MAX_DINOSAURS = 10;
constexpr int HELICOPTER_SPEED = 5;
constexpr int DINO_SPEED = 3;
constexpr int TRUCK_SPEED = 2;
constexpr int DEPOT_WIDTH = 50;
constexpr int DEPOT_HEIGHT = 30;
constexpr int MISSILES_PER_SLOT = 1;
constexpr int TRUCK_CAPACITY = 5;
constexpr int MIN_MISSILES_WARNING = 3;

// Cores
constexpr int SKY_COLOR = 1;
constexpr int GRASS_COLOR = 2;
constexpr int DINO_COLOR = 3;

// Classes
class GameObject {
protected:
    int x, y;
    char direction;

public:
    GameObject(int x = 0, int y = 0, char direction = 'R')
        : x(x), y(y), direction(direction) {}

    int getX() const { return x; }
    int getY() const { return y; }
    char getDirection() const { return direction; }

    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void setDirection(char newDir) { direction = newDir; }
};

class Missile : public GameObject {
private:
    bool active;

public:
    Missile() : GameObject(), active(false) {}

    bool isActive() const { return active; }
    void setActive(bool state) { active = state; }
};

class Dinosaur : public GameObject {
private:
    bool alive;
    int headHeight;

public:
    Dinosaur() : GameObject(), alive(false), headHeight(30) {}

    bool isAlive() const { return alive; }
    void setAlive(bool state) { alive = state; }
    int getHeadHeight() const { return headHeight; }
};

class Helicopter : public GameObject {
private:
    int missiles;
    bool alive;
    bool needReload;
    bool isReloading;

public:
    Helicopter() : GameObject(), missiles(10), alive(true),
        needReload(false), isReloading(false) {}

    int getMissiles() const { return missiles; }
    bool isAlive() const { return alive; }
    bool needsReload() const { return needReload; }
    bool getIsReloading() const { return isReloading; }

    void setMissiles(int count) { missiles = count; }
    void setAlive(bool state) { alive = state; }
    void setNeedReload(bool state) { needReload = state; }
    void setIsReloading(bool state) { isReloading = state; }

    void addMissiles(int count) { missiles += count; }
    void removeMissile() {
        if (missiles > 0) missiles--;
        if (missiles < MIN_MISSILES_WARNING) needReload = true;
    }
};

class Truck : public GameObject {
private:
    int missiles;
    bool isMoving;
    bool isUnloading;

public:
    Truck() : GameObject(), missiles(TRUCK_CAPACITY),
        isMoving(true), isUnloading(false) {}

    int getMissiles() const { return missiles; }
    bool getIsMoving() const { return isMoving; }
    bool getIsUnloading() const { return isUnloading; }

    void setMissiles(int count) { missiles = count; }
    void setIsMoving(bool state) { isMoving = state; }
    void setIsUnloading(bool state) { isUnloading = state; }

    void removeMissile() { if (missiles > 0) missiles--; }
    void reload() { missiles = TRUCK_CAPACITY; }
};

class Depot {
private:
    int x, y;
    vector<bool> slots;
    bool helicopterDocked;
    bool truckDocked;
    mutex mtx;
    condition_variable slotsAvailable;
    condition_variable rechargeComplete;

public:
    Depot() : x(SCREEN_WIDTH - 100), y(SCREEN_HEIGHT - 50),
        slots(10, true), helicopterDocked(false), truckDocked(false) {}

    int getX() const { return x; }
    int getY() const { return y; }
    bool isHelicopterDocked() const { return helicopterDocked; }
    bool isTruckDocked() const { return truckDocked; }

    void setHelicopterDocked(bool state) { helicopterDocked = state; }
    void setTruckDocked(bool state) { truckDocked = state; }

    int countEmptySlots() const {
        return count(slots.begin(), slots.end(), false);
    }

    int countFilledSlots() const {
        return count(slots.begin(), slots.end(), true);
    }

    mutex& getMutex() { return mtx; }
    condition_variable& getSlotsAvailable() { return slotsAvailable; }
    condition_variable& getRechargeComplete() { return rechargeComplete; }

    bool getSlot(int index) const { return slots[index]; }
    void setSlot(int index, bool state) { slots[index] = state; }
};

// Gerenciador de Console
class ConsoleManager {
public:
    static void setConsoleSize() {
        string command = "mode con: cols=" + to_string(SCREEN_WIDTH) +
            " lines=" + to_string(SCREEN_HEIGHT);
        system(command.c_str());
    }

    static void clearScreen() {
        system("cls");
    }

    static void gotoxy(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;

        // SetConsoleCursorPosition move o cursor para a posição especificada
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    static void setColor(int textColor, int backgroundColor) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, (backgroundColor << 4) | textColor);
    }

    static void delay(int ms) {
        this_thread::sleep_for(chrono::milliseconds(ms));
    }
};

// Estado Global do Jogo
class GameState {
private:
    static bool gameRunning;
    static int score;
    static mutex mtx;

public:
    static bool isGameRunning() {
        lock_guard<mutex> lock(mtx);
        return gameRunning;
    }

    static void setGameRunning(bool state) {
        lock_guard<mutex> lock(mtx);
        gameRunning = state;
    }

    static int getScore() {
        lock_guard<mutex> lock(mtx);
        return score;
    }

    static void addScore(int points) {
        lock_guard<mutex> lock(mtx);
        score += points;
    }
};

// Inicialização das variáveis estáticas
bool GameState::gameRunning = true;
int GameState::score = 0;
mutex GameState::mtx;

// Gerenciadores
class RenderManager {
public:
    static void drawScene() {
        char block = 219;
        int skyHeight = SCREEN_HEIGHT * 2 / 3;

        // Primeiro desenha todo o céu
        ConsoleManager::setColor(SKY_COLOR, SKY_COLOR);
        for (int y = 0; y < skyHeight; y++) {
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                ConsoleManager::gotoxy(x, y);
                cout << block;
            }
        }

        // Depois desenha toda a grama
        ConsoleManager::setColor(GRASS_COLOR, GRASS_COLOR );
        for (int y = skyHeight; y < SCREEN_HEIGHT; y++) {
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                ConsoleManager::gotoxy(x, y);
                cout << block;
            }
        }

        ConsoleManager::setColor(7, 0);
    }

    static void drawHelicopter(const Helicopter& heli) {
        ConsoleManager::gotoxy(heli.getX(), heli.getY());
        ConsoleManager::setColor(4, SKY_COLOR);
        if (heli.getDirection() == 'R') {
            cout << "|-H->";
        }
        else {
            cout << "<-H-|";
        }
    }

    static void drawMissile(const Missile& missile) {
        ConsoleManager::gotoxy(missile.getX(), missile.getY());
        ConsoleManager::setColor(4, SKY_COLOR);
        cout << "*";
    }

    static void drawDinosaur(const Dinosaur& dino) {
        ConsoleManager::gotoxy(dino.getX(), dino.getY());
        ConsoleManager::setColor(DINO_COLOR, SKY_COLOR);
        if (dino.getDirection() == 'R') {
            cout << "D>";
        }
        else {
            cout << "<D";
        }
    }

    static void drawDepot(int x,int y) {

        ConsoleManager::gotoxy(x + 10, y + 2); printf("    %c%c%c", 219, 219, 219);
        ConsoleManager::gotoxy(x + 9, y + 3);  printf("   %c%c%c%c%c", 219, 219, 219, 219, 219);
        ConsoleManager::gotoxy(x + 8, y + 4);  printf("  %c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219);
        ConsoleManager::gotoxy(x + 7, y + 5);  printf(" %c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
        ConsoleManager::gotoxy(x + 6, y + 6);  printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);

        // Desenhar o corpo da casa (quadrado) em amarelo
        ConsoleManager::setColor(14, 14);
        for (int i = 7; i <= 11; i++) {
            ConsoleManager::gotoxy(x + 6, y + i);  printf("%c        %c", 219, 219);
        }

        // Desenhar a base da casa (ch�o) em verde
        ConsoleManager::setColor(10, 10);
        ConsoleManager::gotoxy(x + 4, y + 12); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);

        // Desenhar a porta em marrom
        ConsoleManager::setColor(6, 0); // Marrom no fundo preto
        ConsoleManager::gotoxy(x + 8, y + 10); printf("%c%c", 219, 219);
        ConsoleManager::gotoxy(x + 8, y + 11); printf("%c%c", 219, 219);

    }

    static void drawTruck(const Truck& truck) {
        ConsoleManager::gotoxy(truck.getX(), truck.getY());
        ConsoleManager::setColor(8, SKY_COLOR);
        if (truck.getDirection() == 'R') {
            cout << "[TRUCK>]";
        }
        else {
            cout << "[<TRUCK]";
        }
    }

    static void drawStatus(const Helicopter& heli, int dinoCount) {
        ConsoleManager::gotoxy(1, 1);
        ConsoleManager::setColor(7, 0);
        cout << "Mísseis: " << heli.getMissiles()
            << " | Score: " << GameState::getScore()
            << " | Dinos: " << dinoCount;
    }
};

class CollisionManager {
public:
    static bool checkMissileHit(const Missile& missile, const Dinosaur& dino) {
        return (abs(missile.getX() - dino.getX()) < 10 &&
            abs(missile.getY() - (dino.getY() + dino.getHeadHeight())) < 5);
    }

    static bool checkHelicopterCollision(const Helicopter& heli, const Dinosaur& dino) {
        return (abs(heli.getX() - dino.getX()) < 15 &&
            abs(heli.getY() - dino.getY()) < 15);
    }

    static bool isOverDepot(const Helicopter& heli, const Depot& depot) {
        return (abs(heli.getX() - depot.getX()) < DEPOT_WIDTH / 2 &&
            abs(heli.getY() - depot.getY()) < DEPOT_HEIGHT / 2);
    }

    static bool isTruckAtDepot(const Truck& truck, const Depot& depot) {
        return abs(truck.getX() - depot.getX()) < DEPOT_WIDTH / 2;
    }
};

// Classes de Thread
class HelicopterThread {
private:
    Helicopter& helicopter;
    Depot& depot;
    vector<Missile>& missiles;
    mutex& missileMutex;

public:
    HelicopterThread(Helicopter& h, Depot& d, vector<Missile>& m, mutex& mm)
        : helicopter(h), depot(d), missiles(m), missileMutex(mm) {}

    void operator()() {
        while (GameState::isGameRunning()) {
            if (helicopter.needsReload() &&
                CollisionManager::isOverDepot(helicopter, depot) &&
                !helicopter.getIsReloading()) {
                reloadHelicopter();
            }
            ConsoleManager::delay(50);
        }
    }

private:
    void reloadHelicopter() {
        unique_lock<mutex> depotLock(depot.getMutex());

        cout << "Helicóptero iniciando recarga...\n";

        while (depot.isTruckDocked()) {
            cout << "Aguardando caminhão finalizar...\n";
            depot.getSlotsAvailable().wait(depotLock);
        }

        depot.setHelicopterDocked(true);
        helicopter.setIsReloading(true);

        int missilesNeeded = 10 - helicopter.getMissiles();
        int available = depot.countFilledSlots();
        int toLoad = min(missilesNeeded, available);

        if (toLoad > 0) {
            cout << "Recarregando " << toLoad << " mísseis...\n";

            for (int i = 0; i < 10 && toLoad > 0; i++) {
                if (depot.getSlot(i)) {
                    depot.setSlot(i, false);
                    helicopter.addMissiles(1);
                    toLoad--;
                    ConsoleManager::delay(100);
                }
            }

            cout << "Recarga completa! Mísseis: " << helicopter.getMissiles() << "\n";
        }
        else {
            cout << "Depósito vazio! Aguardando reabastecimento...\n";
        }

        helicopter.setNeedReload(helicopter.getMissiles() < MIN_MISSILES_WARNING);
        helicopter.setIsReloading(false);
        depot.setHelicopterDocked(false);

        depot.getRechargeComplete().notify_one();
    }
};

class TruckThread {
private:
    Truck& truck;
    Depot& depot;

public:
    TruckThread(Truck& t, Depot& d) : truck(t), depot(d) {}

    void operator()() {
        while (GameState::isGameRunning()) {
            if (!truck.getIsUnloading()) {
                moveTruck();
            }

            if (truck.getMissiles() > 0 && CollisionManager::isTruckAtDepot(truck, depot)) {
                unloadTruck();
            }

            if (truck.getMissiles() == 0) {
                reloadTruck();
            }

            ConsoleManager::delay(100);
        }
    }

private:
    void moveTruck() {
        if (truck.getDirection() == 'R') {
            if (truck.getX() < SCREEN_WIDTH - 20) {
                truck.setX(truck.getX() + TRUCK_SPEED);
            }
            else {
                truck.setDirection('L');
            }
        }
        else {
            if (truck.getX() > 0) {
                truck.setX(truck.getX() - TRUCK_SPEED);
            }
            else {
                truck.setDirection('R');
            }
        }
    }

    void unloadTruck() {
        unique_lock<mutex> depotLock(depot.getMutex());

        while (depot.isHelicopterDocked()) {
            depot.getRechargeComplete().wait(depotLock);
        }

        depot.setTruckDocked(true);
        truck.setIsUnloading(true);

        int emptySlots = depot.countEmptySlots();
        int toUnload = min(truck.getMissiles(), emptySlots);

        if (toUnload > 0) {
            cout << "Descarregando " << toUnload << " mísseis...\n";

            for (int i = 0; i < 10 && toUnload > 0; i++) {
                if (!depot.getSlot(i)) {
                    depot.setSlot(i, true);
                    truck.removeMissile();
                    toUnload--;
                    ConsoleManager::delay(200);
                }
            }
        }

        truck.setIsUnloading(false);
        depot.setTruckDocked(false);
        depot.getSlotsAvailable().notify_one();
    }

    void reloadTruck() {
        truck.setX(0);
        cout << "Caminhão reabastecendo...\n";
        ConsoleManager::delay(3000);
        truck.reload();
        cout << "Caminhão reabastecido com " << truck.getMissiles() << " mísseis\n";
    }
};
class DinosaurThread {
private:
    vector<Dinosaur>& dinosaurs;
    mutex& dinoMutex;

public:
    DinosaurThread(vector<Dinosaur>& d, mutex& dm)
        : dinosaurs(d), dinoMutex(dm) {}

    void operator()() {
        while (GameState::isGameRunning()) {
            lock_guard<mutex> lock(dinoMutex);
            for (auto& dino : dinosaurs) {
                if (dino.isAlive()) {
                    if (dino.getDirection() == 'R') {
                        if (dino.getX() < SCREEN_WIDTH - 20) {
                            dino.setX(dino.getX() + DINO_SPEED);
                        }
                        else {
                            dino.setDirection('L');
                        }
                    }
                    else {
                        if (dino.getX() > 0) {
                            dino.setX(dino.getX() - DINO_SPEED);
                        }
                        else {
                            dino.setDirection('R');
                        }
                    }
                }
            }
            ConsoleManager::delay(100);
        }
    }
};

class DinosaurGeneratorThread {
private:
    vector<Dinosaur>& dinosaurs;
    mutex& dinoMutex;

public:
    DinosaurGeneratorThread(vector<Dinosaur>& d, mutex& dm)
        : dinosaurs(d), dinoMutex(dm) {}

    void operator()() {
        while (GameState::isGameRunning()) {
            {
                lock_guard<mutex> lock(dinoMutex);
                int aliveCount = count_if(dinosaurs.begin(), dinosaurs.end(),
                    [](const Dinosaur& d) { return d.isAlive(); });

                if (aliveCount < 5) {
                    for (auto& dino : dinosaurs) {
                        if (!dino.isAlive()) {
                            dino.setX(rand() % (SCREEN_WIDTH - 40));
                            dino.setY(SCREEN_HEIGHT * 2 / 3 + 5);  // Logo abaixo da linha do céu
                            dino.setAlive(true);
                            dino.setDirection(rand() % 2 == 0 ? 'L' : 'R');
                            break;
                        }
                    }
                }
            }
            ConsoleManager::delay(2000 + (rand() % 3000));  // 2-5 segundos
        }
    }
};

class RenderThread {
private:
    Helicopter& helicopter;
    vector<Missile>& missiles;
    vector<Dinosaur>& dinosaurs;
    Truck& truck;
    Depot& depot;
    mutex& missileMutex;
    mutex& dinoMutex;

public:
    RenderThread(Helicopter& h, vector<Missile>& m, vector<Dinosaur>& d,
        Truck& t, Depot& dp, mutex& mm, mutex& dm)
        : helicopter(h), missiles(m), dinosaurs(d), truck(t), depot(dp),
        missileMutex(mm), dinoMutex(dm) {}

    void operator()() {
        while (GameState::isGameRunning()) {
            ConsoleManager::clearScreen();
            RenderManager::drawScene();

            RenderManager::drawHelicopter(helicopter);

            {
                lock_guard<mutex> lock(missileMutex);
                for (const auto& missile : missiles) {
                    if (missile.isActive()) {
                        RenderManager::drawMissile(missile);
                    }
                }
            }

            {
                lock_guard<mutex> lock(dinoMutex);
                int aliveCount = 0;
                for (const auto& dino : dinosaurs) {
                    if (dino.isAlive()) {
                        RenderManager::drawDinosaur(dino);
                        aliveCount++;
                    }
                }
                RenderManager::drawStatus(helicopter, aliveCount);
            }

            //RenderManager::drawDepot(depot);
            RenderManager::drawTruck(truck);

            ConsoleManager::delay(50);
        }
    }
};

class InputThread {
private:
    Helicopter& helicopter;
    vector<Missile>& missiles;
    mutex& missileMutex;

public:
    InputThread(Helicopter& h, vector<Missile>& m, mutex& mm)
        : helicopter(h), missiles(m), missileMutex(mm) {}

    void operator()() {
        while (GameState::isGameRunning()) {
            if (!helicopter.getIsReloading()) {
                if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
                    moveHelicopter('L');
                }
                if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
                    moveHelicopter('R');
                }
                if (GetAsyncKeyState(VK_UP) & 0x8000) {
                    moveHelicopter('U');
                }
                if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                    moveHelicopter('D');
                }
                if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
                    shootMissile();
                }
                if (GetAsyncKeyState('X') & 0x8000) {
                    GameState::setGameRunning(false);
                }
            }
            ConsoleManager::delay(10);
        }
    }

private:
    void moveHelicopter(char direction) {
        switch (direction) {
        case 'L':
            if (helicopter.getX() > 0) {
                helicopter.setX(helicopter.getX() - HELICOPTER_SPEED);
                helicopter.setDirection('L');
            }
            break;
        case 'R':
            if (helicopter.getX() < SCREEN_WIDTH - 20) {
                helicopter.setX(helicopter.getX() + HELICOPTER_SPEED);
                helicopter.setDirection('R');
            }
            break;
        case 'U':
            if (helicopter.getY() > 0) {
                helicopter.setY(helicopter.getY() - HELICOPTER_SPEED);
            }
            break;
        case 'D':
            if (helicopter.getY() < SCREEN_HEIGHT - 20) {
                helicopter.setY(helicopter.getY() + HELICOPTER_SPEED);
            }
            break;
        }
    }

    void shootMissile() {
        lock_guard<mutex> lock(missileMutex);

        if (helicopter.getMissiles() > 0) {
            for (auto& missile : missiles) {
                if (!missile.isActive()) {
                    missile.setX(helicopter.getX() +
                        (helicopter.getDirection() == 'R' ? 5 : -1));
                    missile.setY(helicopter.getY());
                    missile.setActive(true);
                    missile.setDirection(helicopter.getDirection());
                    helicopter.removeMissile();
                    break;
                }
            }
        }
    }
};

int main() {
    // Configuração do console
    ConsoleManager::setConsoleSize();
    ConsoleManager::clearScreen();

    // Criação dos objetos do jogo
    Helicopter helicopter;
    Truck truck;
    truck.setY(SCREEN_HEIGHT - 5);
    truck.setX(SCREEN_WIDTH - 130);
    Depot depot;
    vector<Missile> missiles(MAX_MISSILES);
    vector<Dinosaur> dinosaurs(MAX_DINOSAURS);

    // Mutexes
    mutex missileMutex;
    mutex dinoMutex;

    // Criação das threads
    vector<thread> threads;

    // Thread do helicóptero
    threads.emplace_back(HelicopterThread(helicopter, depot, missiles, missileMutex));

    // Thread do caminhão
    threads.emplace_back(TruckThread(truck, depot));

    // Thread dos mísseis
    threads.emplace_back([&]() {
        while (GameState::isGameRunning()) {
            lock_guard<mutex> lock(missileMutex);
            for (auto& missile : missiles) {
                if (missile.isActive()) {
                    if (missile.getDirection() == 'R') {
                        missile.setX(missile.getX() + 2);
                    }
                    else {
                        missile.setX(missile.getX() - 2);
                    }

                    // Desativa míssil se sair da tela
                    if (missile.getX() < 0 || missile.getX() > SCREEN_WIDTH) {
                        missile.setActive(false);
                    }
                }
            }
            ConsoleManager::delay(50);
        }
        });

    // Thread dos dinossauros
    threads.emplace_back(DinosaurThread(dinosaurs, dinoMutex));

    // Thread geradora de dinossauros
    threads.emplace_back(DinosaurGeneratorThread(dinosaurs, dinoMutex));

    // Thread de colisões
    threads.emplace_back([&]() {
        while (GameState::isGameRunning()) {
            {
                lock_guard<mutex> lockMissile(missileMutex);
                lock_guard<mutex> lockDino(dinoMutex);

                // Verifica colisões de mísseis com dinossauros
                for (auto& missile : missiles) {
                    if (missile.isActive()) {
                        for (auto& dino : dinosaurs) {
                            if (dino.isAlive() &&
                                CollisionManager::checkMissileHit(missile, dino)) {
                                missile.setActive(false);
                                dino.setAlive(false);
                                GameState::addScore(100);
                            }
                        }
                    }
                }

                // Verifica colisões do helicóptero com dinossauros
                for (const auto& dino : dinosaurs) {
                    if (dino.isAlive() &&
                        CollisionManager::checkHelicopterCollision(helicopter, dino)) {
                        helicopter.setAlive(false);
                        GameState::setGameRunning(false);
                        cout << "\nGame Over: Helicóptero destruído!\n";
                    }
                }
            }
            ConsoleManager::delay(50);
        }
        });

    // Thread de renderização
    threads.emplace_back(RenderThread(helicopter, missiles, dinosaurs, truck, depot,
        missileMutex, dinoMutex));

    // Thread de input
    threads.emplace_back(InputThread(helicopter, missiles, missileMutex));

    // Loop principal
    while (GameState::isGameRunning()) {
        {
            lock_guard<mutex> lock(dinoMutex);
            int aliveCount = count_if(dinosaurs.begin(), dinosaurs.end(),
                [](const Dinosaur& d) { return d.isAlive(); });

            if (aliveCount >= 5) {
                cout << "\nGame Over: Terra condenada - 5 ou mais dinossauros vivos!\n";
                GameState::setGameRunning(false);
            }
        }
        ConsoleManager::delay(100);
    }

    // Aguarda todas as threads terminarem
    for (auto& t : threads) {
        t.join();
    }

    // Mensagem final
    ConsoleManager::clearScreen();
    cout << "\nJogo finalizado!\n";
    cout << "Pontuação final: " << GameState::getScore() << "\n";

    return 0;
}

