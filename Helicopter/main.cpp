#include "console_maneger.h"  // para usar as funções de console
#include "game.h"
#include "render_manager.h" 



int main() {
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Largura dos caracteres
    cfi.dwFontSize.Y = 12;                  // Altura
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    system("mode con: lines=116 cols=328");
    char ch = 0;
    int i, frente = true, x, coluna;
    ConsoleManeger::getup();
    RenderManager::drawScene();
    RenderManager::drawDepot(139, 27);
    srand(time(NULL));
    while (true) {
        for (coluna = 0; coluna < 300; coluna++) {
            RenderManager::moveHelicopterRight(coluna, 75);
            ConsoleManeger::delay(10);
            RenderManager::eraseHelicopter(coluna, 75);
        }
        for (coluna = 300; coluna > 218; coluna--) {
            RenderManager::moveTruckLeft(coluna, 98);
            ConsoleManeger::delay(100);
            RenderManager::eraseTruckRight(coluna, 98);
        }
        for (coluna = 218; coluna <= 300; coluna++) {
            RenderManager::moveTruckRight(coluna, 98);
            ConsoleManeger::delay(100);
            RenderManager::eraseTruckLeft(coluna, 98);
        }

        while (true) {
            if (frente) {
                RenderManager::moveDinoLeft(rand() % 2, x, 74);x++;
            }
            if (x == 140) frente = false;
            if (!frente) {
                RenderManager::moveDinoLeft(rand() % 2, x, 74);
                x--;
            }
            if (x == 2) frente = true;
        }
    }
}