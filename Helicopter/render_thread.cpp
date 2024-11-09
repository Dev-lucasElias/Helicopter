// render_thread.cpp
#include "render_thread.h"

RenderThread::RenderThread(Helicopter& h, std::vector<Missile>& m, std::vector<Dinosaur>& d,
    Truck& t, Depot& dp, std::mutex& mm, std::mutex& dm)
    : helicopter(h), missiles(m), dinosaurs(d), truck(t), depot(dp),
    missileMutex(mm), dinoMutex(dm) {}

void RenderThread::operator()() {
    while (GameState::isGameRunning()) {
        ConsoleManager::clearScreen();
        RenderManager::drawScene();

        RenderManager::drawHelicopter(helicopter);

        {
            std::lock_guard<std::mutex> lock(missileMutex);
            for (const auto& missile : missiles) {
                if (missile.isActive()) {
                    RenderManager::drawMissile(missile);
                }
            }
        }

        {
            std::lock_guard<std::mutex> lock(dinoMutex);
            int aliveCount = 0;
            for (const auto& dino : dinosaurs) {
                if (dino.isAlive()) {
                    RenderManager::drawDinosaur(dino);
                    aliveCount++;
                }
            }
            RenderManager::drawStatus(helicopter, aliveCount);
        }

        RenderManager::drawDepot(depot);
        RenderManager::drawTruck(truck);

        ConsoleManager::delay(50);
    }
}