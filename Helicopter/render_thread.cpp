// render_thread.cpp
#include "render_thread.h"

RenderThread::RenderThread(Helicopter& h, std::vector<Missile>& m, std::vector<Dinosaur>& d,
    Truck& t, Depot& dp, std::mutex& mm, std::mutex& dm)
    : helicopter(h), missiles(m), dinosaurs(d), truck(t), depot(dp),
    missileMutex(mm), dinoMutex(dm) {}

void RenderThread::operator()() {
    while (GameState::isGameRunning()) {
        //// Limpa tela e redesenha cen�rio
        //ConsoleManeger::clearScreen();
        //RenderManager::drawScene();

        // Desenha helic�ptero
        /*if (helicopter.getDirection() == 'R') {
            RenderManager::moveHelicopterRight(helicopter.getX(), helicopter.getY());
        }
        else {
            RenderManager::moveHelicopterLeft(helicopter.getX(), helicopter.getY());
        }*/

        //// Desenha m�sseis
        //{
        //    std::lock_guard<std::mutex> lock(missileMutex);
        //    for (const auto& missile : missiles) {
        //        if (missile.isActive()) {
        //            if (missile.getDirection() == 'R') {
        //                RenderManager::moveMissileRight(missile.getX(), missile.getY());
        //            }
        //            else {
        //                RenderManager::moveMissileLeft(missile.getX(), missile.getY());
        //            }
        //        }
        //    }
        //}
         
        
        // Desenha dep�sito
        RenderManager::drawDepot(116, 20);

        // Desenha dinossauros
        {
            std::lock_guard<std::mutex> lock(dinoMutex);
            for (const auto& dino : dinosaurs) {
                if (dino.isAlive()) {
                        ConsoleManeger::gotoxy(dino.getX(), dino.getY());
                    if (dino.getDirection() == 'R') {
                        RenderManager::moveDinoRight(0, dino.getX(), dino.getY());
                    }
                    else {
                        RenderManager::moveDinoLeft(0, dino.getX(), dino.getY());
                    }
                }
            }
        }


        //// Desenha caminh�o
        //if (truck.getDirection() == 'R') {
        //    RenderManager::moveTruckRight(truck.getX(), truck.getY());
        //}
        //else {
        //    RenderManager::moveTruckLeft(truck.getX(), truck.getY());
        //}

        ConsoleManeger::delay(40);  // Delay para controlar FPS
    }
}