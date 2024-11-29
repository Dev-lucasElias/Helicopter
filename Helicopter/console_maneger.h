#ifndef CONSOLE_MANAGER_H
#define CONSOLE_MANAGER_H
#pragma once
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <mutex>

class ConsoleManeger {
private:
    // Mutex est�tico para controle de acesso ao console
    static std::mutex consoleMutex;

public:
    static void setConsoleSize(int width, int height);
    static void setColor(int textColor, int backgroundColor);
    static void gotoxy(int x, int y);
    static void delay(unsigned int mseconds);
    static void clearScreen();
    static void getup();

    // Nova fun��o que combina gotoxy e printf em uma opera��o at�mica
    static void print(int x, int y, const char* format, ...);

    // M�todo para obter o mutex (caso outras classes precisem sincronizar com o console)
    static std::mutex& getMutex() { return consoleMutex; }
};
#endif