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
    // Mutex estático para controle de acesso ao console
    static std::mutex consoleMutex;

public:
    static void setConsoleSize(int width, int height);
    static void setColor(int textColor, int backgroundColor);
    static void gotoxy(int x, int y);
    static void delay(unsigned int mseconds);
    static void clearScreen();
    static void getup();

    // Nova função que combina gotoxy e printf em uma operação atômica
    static void print(int x, int y, const char* format, ...);

    // Método para obter o mutex (caso outras classes precisem sincronizar com o console)
    static std::mutex& getMutex() { return consoleMutex; }
};
#endif