// main.cpp
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include "game.h"
#include "helicopter.h"
#include "truck.h"
#include "depot.h"
#include "missile.h"
#include "dinosaur.h"
#include "render_manager.h"
#include "console_maneger.h"
#include "helicopter_thread.h"
#include "truck_thread.h"
#include "render_thread.h"
#include "input_thread.h"
#include "game_state.h"

int main() {
    ConsoleManeger::setConsoleSize(156,55);

    // Criação dos objetos do jogo
    Helicopter helicopter;
    Truck truck;
    Depot depot;
    std::vector<Missile> missiles(MAX_MISSILES);
    std::vector<Dinosaur> dinosaurs(MAX_DINOSAURS);

    // Mutexes
    std::mutex missileMutex;
    std::mutex dinoMutex;

    // Criação das threads
    std::vector<std::thread> threads;

    // Inicializa as threads
    threads.emplace_back(HelicopterThread::(helicopter, depot, missiles, missileMutex));
    threads.emplace_back(TruckThread(truck, depot));
    threads.emplace_back(RenderThread(helicopter, missiles, dinosaurs, truck, depot,
        missileMutex, dinoMutex));
    threads.emplace_back(InputThread(helicopter, missiles, missileMutex));

    // Loop principal
    while (GameState::isGameRunning()) {
        {
            std::lock_guard<std::mutex> lock(dinoMutex);
            int aliveCount = std::count_if(dinosaurs.begin(), dinosaurs.end(),
                [](const Dinosaur& d) { return d.isAlive(); });

            if (aliveCount >= 5) {
                std::cout << "\nGame Over: Terra condenada - 5 ou mais dinossauros vivos!\n";
                GameState::setGameRunning(false);
            }
        }
        ConsoleManeger::delay(100);
    }

    // Aguarda todas as threads terminarem
    for (auto& t : threads) {
        t.join();
    }

    // Mensagem final
    ConsoleManeger::clearScreen();
    std::cout << "\nJogo finalizado!\n";
    std::cout << "Pontuação final: " << GameState::getScore() << "\n";

    return 0;
}