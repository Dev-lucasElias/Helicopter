#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

// Includes da biblioteca padrão
#include <iostream>
#include <windows.h>

// Includes do projeto
#include "console_maneger.h"
#include "game.h"

class RenderManager {
public:
    // Funções de desenho base
    static void drawScene();
    static void drawDepot(int x, int y);  // Corrigido nome

    // Funções de movimento
    static void moveDinoRight(int jump, int x, int y);
    static void moveDinoLeft(int jump, int x, int y);
    static void moveHelicopterRight(int x, int y);
    static void moveHelicopterLeft(int x, int y);
    static void moveTruckRight(int x, int y);
    static void moveTruckLeft(int x, int y);
    static void moveMissileRight(int x, int y);
    static void moveMissileLeft(int x, int y);

    // Funções de limpeza
    static void eraseDino(int jump, int x, int y);
    static void eraseTruckLeft(int x, int y);
    static void eraseTruckRight(int x, int y);
    static void eraseHelicopter(int x, int y);

private:
    // Constantes de cor (se não estiverem em game.h)
    static const int SKY_COLOR = 1;    // Azul
    static const int GRASS_COLOR = 2;  // Verde
    static const int DINO_COLOR = 3;   // Verde claro
};

#endif // RENDER_MANAGER_H