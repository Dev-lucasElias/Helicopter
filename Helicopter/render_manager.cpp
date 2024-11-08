#include "render_manager.h"

void RenderManager::drawScene() {
    {
        char block = 219;
        int skyHeight = SCREEN_HEIGHT * 2 / 3;

        // Primeiro desenha todo o céu
        //ConsoleManager::setColor(SKY_COLOR, SKY_COLOR);
        for (int y = 0; y < skyHeight; y++) {
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                //ConsoleManager::gotoxy(x, y);
                cout << block;
            }
        }

        // Depois desenha toda a grama
        //ConsoleManager::setColor(GRASS_COLOR, GRASS_COLOR);
        for (int y = skyHeight; y < SCREEN_HEIGHT; y++) {
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                //ConsoleManager::gotoxy(x, y);
                cout << block;
            }
        }

       // ConsoleManager::setColor(7, 0);
    }
}

void RenderManager::drawDepotHouse(int x, int y) {
    // Desenhar o teto da casa 
    ConsoleManager::setColor(4, 4);
    ConsoleManager::gotoxy(x + 10, y + 2);
    cout << string(3, (char)219);  // Usando string para repetir o caractere

    ConsoleManager::gotoxy(x + 9, y + 3);
    cout << string(5, (char)219);
    // ... resto do código do desenho
}