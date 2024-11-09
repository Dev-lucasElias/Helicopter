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
    int i, frente = true, x=0, coluna;
    ConsoleManeger::getup();
    RenderManager::drawScene();
    RenderManager::drawDepot(139, 27);
    srand(time(NULL));
    while (true) {
        for (coluna = 0; coluna < 70; coluna++) {
            RenderManager::moveHelicopterRight(coluna, 15);
            ConsoleManeger::delay(10);
            RenderManager::eraseHelicopter(coluna, 15);
        }
        /*for (coluna = 70; coluna > 58; coluna--) {
            RenderManager::moveTruckLeft(coluna, 35);
            ConsoleManeger::delay(100);
            RenderManager::eraseTruckRight(coluna, 35);
        }
        for (coluna = 58; coluna <= 70; coluna++) {
            RenderManager::moveTruckRight(coluna, 35);
            ConsoleManeger::delay(100);
            RenderManager::eraseTruckLeft(coluna, 35);
        }*/

        while (true) {
            if (frente) {
                RenderManager::moveDinoLeft(rand() % 2, x, 10);x++;
            }
            if (x == 120) frente = false;
            if (!frente) {
                RenderManager::moveDinoLeft(rand() % 2, x, 10);
                x--;
            }
            if (x == 2) frente = true;
        }
    }
}