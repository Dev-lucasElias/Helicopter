#include "console_maneger.h"




void ConsoleManeger::setConsoleSize(int width, int height) {
    char command[30];
    sprintf_s(command, "mode con: cols=%d lines=%d", width, height);
    system(command);
}

void ConsoleManeger::setColor(int textColor, int backgroundColor) {
    // Muda a cor do texto e do fundo
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (backgroundColor << 4) | textColor);
}

void ConsoleManeger::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ConsoleManeger::delay(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

// No console_manager.cpp
void ConsoleManeger::clearScreen() {
    system("cls");  // Para Windows
}

void ConsoleManeger::getup()
{
    system("cls");
    gotoxy(10, 2);
    printf("Press X to Exit, Press Space to Jump");
    gotoxy(62, 2);
    printf("SCORE : ");
    gotoxy(1, 25);
    for (int x = 0;x < 79;x++)
        printf("-");
}
