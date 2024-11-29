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
#include "dinosaur_thread.h"
#include "truck_thread.h"
#include "render_thread.h"
#include "input_thread.h"
#include "game_state.h"

int main() {
    // Configuração inicial
    ConsoleManeger::setConsoleSize(133, 33);
    RenderManager::drawScene();

    // Criação dos objetos
    Helicopter helicopter;
    Truck truck;
    Depot depot;
    vector<Missile> missiles(MAX_MISSILES);
    vector<Dinosaur> dinosaurs(MAX_DINOSAURS);

    // Mutexes
    mutex missileMutex;
    mutex dinoMutex;


    // Inicializa posições iniciais
    dinosaurs[0].setX(60);
    dinosaurs[0].setY(24);
    dinosaurs[0].setAlive(true);

    // Criar e iniciar threads
    vector<thread> threads;
    threads.emplace_back(DinosaurThread(dinosaurs[0], dinoMutex));
    //threads.emplace_back(HelicopterThread(helicopter, depot, missiles, missileMutex));
    //threads.emplace_back(TruckThread(truck, depot));
    threads.emplace_back(RenderThread(helicopter, missiles, dinosaurs, truck, depot, missileMutex, dinoMutex));

    //// Loop principal do jogo
    //bool frente = true;
    //int x = 2;
    //while (GameState::isGameRunning()) {
    //    if (frente) {
    //        RenderManager::moveDinoRight(rand() % 2, x, 24);
    //        x++;
    //        if (x == 130) frente = false;
    //    }
    //    if (!frente) {
    //        RenderManager::moveDinoLeft(rand() % 2, x, 24);
    //        x--;
    //        if (x == 5) frente = true;
    //    }

    //    ConsoleManeger::delay(100);
    //}

    // Aguarda threads terminarem
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}