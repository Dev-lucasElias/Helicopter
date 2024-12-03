#ifndef GAME_H  // Guarda de inclusão
#define GAME_H

#include <iostream>
#include <windows.h>

namespace GameConstants {  // Coloca as constantes em um namespace para evitar conflitos
    constexpr int SCREEN_WIDTH = 133;
    constexpr int SCREEN_HEIGHT = 33;
    constexpr int MAX_MISSILES = 10;
    constexpr int MAX_DINOSAURS = 3;
    constexpr int MISSILE_SPEED = 3;
    constexpr int HELICOPTER_SPEED = 1;
    constexpr int HELICOPTER_WIDTH = 14;
    constexpr int HELICOPTER_HEIGHT = 6;
    constexpr int DINO_SPEED = 1;
    constexpr int TRUCK_SPEED = 2;
    constexpr int DEPOT_WIDTH = 50;
    constexpr int DEPOT_HEIGHT = 30;
    constexpr int MIN_MISSILES_WARNING = 3;
    constexpr int TRUCK_CAPACITY = 2;
    const int SKY_HEIGHT = SCREEN_HEIGHT * 2 / 3;
    const int GROUND_LEVEL = SKY_HEIGHT;
    const int DINO_HEIGHT = 9;  // Altura total do sprite do dinossauro
    const int DINO_WIDTH = 17;
    // Cores
    constexpr int SKY_COLOR = 1;    // Azul
    constexpr int GRASS_COLOR = 2;  // Verde
    constexpr int DINO_COLOR = 3;   // Verde claro
}

using namespace GameConstants;  

#endif // GAME_H