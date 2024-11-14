#ifndef GAME_H  // Guarda de inclusão
#define GAME_H

#include <iostream>
#include <windows.h>

namespace GameConstants {  // Coloca as constantes em um namespace para evitar conflitos
    constexpr int SCREEN_WIDTH = 156;
    constexpr int SCREEN_HEIGHT = 40;
    constexpr int MAX_MISSILES = 10;
    constexpr int MAX_DINOSAURS = 3;
    constexpr int HELICOPTER_SPEED = 3;
    constexpr int DINO_SPEED = 1;
    constexpr int TRUCK_SPEED = 2;
    constexpr int DEPOT_WIDTH = 50;
    constexpr int DEPOT_HEIGHT = 30;
    constexpr int MIN_MISSILES_WARNING = 3;
    constexpr int TRUCK_CAPACITY = 2;

    // Cores
    constexpr int SKY_COLOR = 1;    // Azul
    constexpr int GRASS_COLOR = 2;  // Verde
    constexpr int DINO_COLOR = 3;   // Verde claro
}

using namespace GameConstants;  

#endif // GAME_H