#ifndef CONSOLE_MANAGER_H
#define CONSOLE_MANAGER_H
#include "render_manager.h"
#include "game.h"

// No console_manager.h
class ConsoleManeger {
public:
    static void setColor(int textColor, int backgroundColor);
    static void setConsoleSize(int width, int height);
    static void gotoxy(int x, int y);
    static void delay(unsigned int mseconds);
    static void getup();
    static void clearScreen(); 
};
#endif