// render_thread.cpp
#include "render_thread.h"

RenderThread::RenderThread(Helicopter& h, std::vector<Missile>& m, std::vector<Dinosaur>& d,
    Truck& t, Depot& dp, std::mutex& mm, std::mutex& dm)
    : helicopter(h), missiles(m), dinosaurs(d), truck(t), depot(dp),
    missileMutex(mm), dinoMutex(dm) {}

void RenderThread::operator()() {
    int lastX = helicopter.getX();
    int lastY = helicopter.getY();

    while (GameState::isGameRunning()) {
        // Se a posição do helicóptero mudou, precisamos limpar a posição anterior
        RenderSync::beginRender();

        if (lastX != helicopter.getX() || lastY != helicopter.getY()) {
            RenderManager::eraseHelicopter(lastX, lastY);
            RenderManager::drawScene(lastX - 2, lastY, lastX + 20, lastY + 8);  // Área afetada pelo helicóptero
            lastX = helicopter.getX();
            lastY = helicopter.getY();
        }



        if (helicopter.getX() >= 0 &&
            helicopter.getX() <= SCREEN_WIDTH - 20 &&
            helicopter.getY() >= 0 &&
            helicopter.getY() <= SCREEN_HEIGHT - 8) {
            if (helicopter.getDirection() == 'R') {
                RenderManager::moveHelicopterRight(helicopter.getX(), helicopter.getY());
            }
            else {
                RenderManager::moveHelicopterLeft(helicopter.getX(), helicopter.getY());
            }
        }

        // Desenha depósito
        RenderManager::drawDepot(116, 20);

        {
            std::lock_guard<std::mutex> lock(dinoMutex);
            for (const auto& dino : dinosaurs) {
                if (dino.isAlive() &&
                    dino.getY() >= 0 &&
                    dino.getY() + DINO_HEIGHT <= SCREEN_HEIGHT) {
                    if (dino.getDirection() == 'R') {
                        RenderManager::moveDinoRight(0, dino.getX(), dino.getY());
                    }
                    else {
                        RenderManager::moveDinoLeft(0, dino.getX(), dino.getY());
                    }
                }
            }
        }
        RenderSync::endRender();
        ConsoleManeger::delay(50);  // Delay para controlar FPS
    }
}