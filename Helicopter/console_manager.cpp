// console_manager.cpp
#include "console_maneger.h"
#include <stdarg.h>

// Inicializa o mutex estático
std::mutex ConsoleManeger::consoleMutex;

void ConsoleManeger::setConsoleSize(int width, int height) {

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { (SHORT)width, (SHORT)height };
    SetConsoleScreenBufferSize(handle, coord);
}

void ConsoleManeger::setColor(int textColor, int backgroundColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor * 16 + textColor);
}

void ConsoleManeger::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ConsoleManeger::print(int x, int y, const char* format, ...) {

    // Move o cursor
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void ConsoleManeger::delay(unsigned int mseconds) {
    Sleep(mseconds);
}
void ConsoleManeger::colorPrint(int x, int y, int textColor, int bgColor, const char* format, ...) {

    // Define a cor
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bgColor * 16 + textColor);

    // Move o cursor
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    // Prepara os argumentos variáveis
    va_list args;
    va_start(args, format);
    // Imprime usando os argumentos variáveis
    vprintf(format, args);
    va_end(args);
}

void ConsoleManeger::clearScreen() {
    system("cls");
}