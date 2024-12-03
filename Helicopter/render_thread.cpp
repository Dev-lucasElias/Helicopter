// render_thread.cpp
#include "render_thread.h"

RenderThread::RenderThread(Helicopter& h, std::vector<Missile>& m, std::vector<Dinosaur>& d,
    Truck& t, Depot& dp, std::mutex& mm, std::mutex& dm)
    : helicopter(h), missiles(m), dinosaurs(d), truck(t), depot(dp),
    missileMutex(mm), dinoMutex(dm) {}

void RenderThread::operator()() {
    int lastX = helicopter.getX();
    int lastY = helicopter.getY();
    
    // Vamos manter um registro das últimas posições dos mísseis para limpar seus rastros
    std::vector<std::pair<int, int>> lastMissilePositions;

    while (GameState::isGameRunning()) {

        

        //Limpa rastro do helicoptero
        if (lastX != helicopter.getX() || lastY != helicopter.getY()) {
            RenderManager::drawScene(lastX - 2, lastY, lastX + 20, lastY + 8);  // Área afetada pelo helicóptero
            lastX = helicopter.getX();
            lastY = helicopter.getY();
        }
        if (helicopter.getY() >= 0 &&
            helicopter.getY() <= SCREEN_HEIGHT - 8) {
            RenderManager::moveHelicopter(5, helicopter.getY());
        }

        // Atualiza e renderiza mísseis
        {
            std::lock_guard<std::mutex> lock(missileMutex);
            for (auto& missile : missiles) {
                if (missile.isActive()) {
                    // Guarda posição atual
                    Position oldPos = missile.getPosition();

                    // Atualiza posição
                    missile.update();
                    Position newPos = missile.getPosition();

                    // Limpa uma área um pouco maior que o míssil para garantir que não fiquem rastros
                    for (int i = -1; i <= 1; i++) {  // Limpa uma área de 3 pixels de largura
                        if (oldPos.y < SCREEN_HEIGHT * 2 / 3) {
                            ConsoleManeger::colorPrint(
                                static_cast<int>(oldPos.x) + i,  // Inclui pixels adjacentes
                                static_cast<int>(oldPos.y + 2),
                                SKY_COLOR, SKY_COLOR, "%c", 219
                            );
                        }
                        else {
                            ConsoleManeger::colorPrint(
                                static_cast<int>(oldPos.x) + i,
                                static_cast<int>(oldPos.y + 2),
                                GRASS_COLOR, GRASS_COLOR, "%c", 219
                            );
                        }
                    }

                    // Renderiza na nova posição apenas se estiver dentro da tela
                    if (newPos.x < SCREEN_WIDTH) {
                        ConsoleManeger::colorPrint(
                            static_cast<int>(newPos.x),
                            static_cast<int>(oldPos.y + 2),
                            4, 4, "%c", 219
                        );
                    }
                    else {
                        missile.deactivate();
                    }
                }
            }

            // Remove mísseis inativos
            missiles.erase(
                std::remove_if(missiles.begin(), missiles.end(),
                    [](const Missile& m) { return !m.isActive(); }),
                missiles.end()
            );
        }

        

        //Renderiza dinoosauro
        {
            for (const auto& dino : dinosaurs) {
                if (dino.isAlive() &&
                    dino.getY() >= 0 &&
                    dino.getY() - DINO_HEIGHT <= SCREEN_HEIGHT) {
                    if (dino.getDirection() == 'R') {
                        RenderManager::moveDinoRight(0, dino.getX(), dino.getY());
                    }
                    else {
                        RenderManager::moveDinoLeft(0, dino.getX(), dino.getY());
                    }
                }
            }
        }
        ConsoleManeger::delay(10);  // Delay para controlar FPS
    }
}