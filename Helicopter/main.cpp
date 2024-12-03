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
    // Configura��o inicial
    ConsoleManeger::setConsoleSize(133, 33);
    //Renderiza cen�rio
    RenderManager::drawScene();
    // Desenha dep�sito
    RenderManager::drawDepot(116, 20);

    // Cria��o dos objetos
    Helicopter helicopter;  // Centro da tela
    helicopter.setY(SCREEN_HEIGHT / 2); // Meio da altura
    Truck truck;
    Depot depot;
    vector<Missile> missiles(MAX_MISSILES);
    vector<Dinosaur> dinosaurs(MAX_DINOSAURS);

    // Mutexes
    mutex missileMutex;
    mutex dinoMutex;
    mutex helicopterMutex;


    // Inicializa posi��es iniciais
    dinosaurs[0].setX(60);
    dinosaurs[0].setY(43);
    dinosaurs[0].setAlive(true);

    // Criar e iniciar threads
    vector<thread> threads;
    threads.emplace_back(DinosaurThread(dinosaurs[0], dinoMutex));
    threads.emplace_back(HelicopterThread(helicopter, depot, missiles, missileMutex));
    threads.emplace_back(InputThread(helicopter, missiles, missileMutex, helicopterMutex));
    threads.emplace_back(InputThread(helicopter, missiles, missileMutex, helicopterMutex));
    threads.emplace_back(RenderThread(helicopter, missiles, dinosaurs, truck, depot, missileMutex, dinoMutex));

    

    // Aguarda threads terminarem
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}