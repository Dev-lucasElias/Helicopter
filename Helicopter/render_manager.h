// Em render_manager.h (Arquivos de Cabe�alho/Managers/render_manager.h)
#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "console_maneger.h"  // para usar as fun��es de console
// ... outros includes necess�rios

class RenderManager {
public:
    static void drawScene();
    static void drawHelicopter(const Helicopter& helicopter);
    static void drawDepoit();
    static void drawTruck();
    static void drawDepoit();
    static void eraseDino();
    static void eraseTruck();
    static void eraseHelicopter();
    static void moveDinoRight();
    static void moveDinoLeft();
    static void moveHelicopterRight();
    static void moveHelicopterLeft();
    static void moveTruckRight();
    static void moveTruckLeft();
    static void moveMissileRight();
    static void moveMissileLeft();

};

#endif
