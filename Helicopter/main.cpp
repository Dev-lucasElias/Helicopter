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
    // Criação dos objetos do jogo
    ConsoleManeger::setConsoleSize(133, 33);
    RenderManager::drawScene();
    RenderManager::drawDepot(116,20);
    RenderManager::drawDino(60,24); //box dino = 17x9


}