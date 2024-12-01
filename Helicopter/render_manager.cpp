#include "render_manager.h"
#include "console_maneger.h"
#include "game.h"
using namespace std;

int RenderManager::posicaoHelice = 0;
int t, speed = 40;

void RenderManager::drawScene(int startX, int startY, int endX, int endY) {
    char block = 219;  
    int skyHeight = SCREEN_HEIGHT * 2 / 3;  

    startX = max(0, startX);
    startY = max(0, startY);
    endX = min(SCREEN_WIDTH, endX);
    endY = min(SCREEN_HEIGHT, endY);

    for (int y = startY; y < min(skyHeight, endY); y++) {
        for (int x = startX; x < endX; x++) {
            ConsoleManeger::colorPrint(x, y, SKY_COLOR, SKY_COLOR, "%c", block);
        }
    }

    for (int y = max(skyHeight, startY); y < endY; y++) {
        for (int x = startX; x < endX; x++) {
            ConsoleManeger::colorPrint(x, y, GRASS_COLOR, GRASS_COLOR, "%c", block);
        }
    }
}

void RenderManager::drawScene() {
    drawScene(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void RenderManager::drawDepot(int x, int y) {
    char block = 219;  

    ConsoleManeger::colorPrint(x + 10, y + 2, 4, 4, "    %c%c%c", block, block, block);
    ConsoleManeger::colorPrint(x + 9, y + 3, 4, 4, "   %c%c%c%c%c",
        block, block, block, block, block);
    ConsoleManeger::colorPrint(x + 8, y + 4, 4, 4, "  %c%c%c%c%c%c%c",
        block, block, block, block, block, block, block);
    ConsoleManeger::colorPrint(x + 7, y + 5, 4, 4, " %c%c%c%c%c%c%c%c%c",
        block, block, block, block, block, block, block, block, block);
    ConsoleManeger::colorPrint(x + 6, y + 6, 4, 4, "%c%c%c%c%c%c%c%c%c%c%c",
        block, block, block, block, block, block, block, block, block, block, block);
    for (int i = 7; i <= 11; i++) {
        ConsoleManeger::colorPrint(x + 6, y + i, 14, 14, "%c         %c", block, block);
    }

    ConsoleManeger::colorPrint(x - 5, y + 12, 15, 13, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
        block, block, block, block, block, block, block, block, block, block, block,
        block, block, block, block, block, block, block, block, block, block, block);

    ConsoleManeger::colorPrint(x + 8, y + 9, 6, 0, "%c%c", block, block);
    ConsoleManeger::colorPrint(x + 8, y + 10, 6, 0, "%c%c", block, block);
}

void RenderManager::drawDino(int x, int y) {
    char block = 219;
    ConsoleManeger::colorPrint(x, y, DINO_COLOR, GRASS_COLOR, "         %c%c%c%c%c%c%c%c",
        block, block, block, block, block, block, block, block);

    ConsoleManeger::colorPrint(x, y + 1, DINO_COLOR, GRASS_COLOR, "         %c%c", block, block);
    ConsoleManeger::colorPrint(x + 11, y + 1, 4, GRASS_COLOR, "%c", block);
    ConsoleManeger::colorPrint(x + 12, y + 1, DINO_COLOR, GRASS_COLOR, "%c%c%c%c%c",
        block, block, block, block, block);

    ConsoleManeger::colorPrint(x, y + 2, DINO_COLOR, GRASS_COLOR, "         %c%c%c%c%c%c%c ",
        block, block, block, block, block, block, block);

    ConsoleManeger::colorPrint(x, y + 3, DINO_COLOR, GRASS_COLOR, " %c      %c%c%c%c%c%c%c%c ",
        block, block, block, block, block, block, block, block, block);

    ConsoleManeger::colorPrint(x, y + 4, DINO_COLOR, GRASS_COLOR, " %c%c%c  %c%c%c%c%c%c%c%c%c%c ",
        block, block, block, block, block, block, block, block, block, block, block, block, block);

    ConsoleManeger::colorPrint(x, y + 5, DINO_COLOR, GRASS_COLOR, " %c%c%c%c%c%c%c%c%c%c%c%c  %c ",
        block, block, block, block, block, block, block, block, block, block, block, block, block);

    ConsoleManeger::colorPrint(x, y + 6, DINO_COLOR, GRASS_COLOR, "   %c%c%c%c%c%c%c%c%c     ",
        block, block, block, block, block, block, block, block, block);

    ConsoleManeger::colorPrint(x, y + 7, DINO_COLOR, GRASS_COLOR, "    %c%c%c %c%c       ",
        block, block, block, block, block);

    ConsoleManeger::colorPrint(x, y + 8, DINO_COLOR, GRASS_COLOR, "    %c%c   %c%c      ",
        block, block, block, block);
}

void RenderManager::eraseDino(int x, int y) {
    int skyHeight = SCREEN_HEIGHT * 2 / 3;
    for (int i = 0; i <= 8; i++) {
        int color = (y + i >= skyHeight) ? GRASS_COLOR : SKY_COLOR;
        ConsoleManeger::colorPrint(x, y + i, color, color, "                 ");
    }
}

void RenderManager::moveDinoRight(int jump, int x, int y) {
    drawDino(x, y);
    ConsoleManeger::delay(speed);
    eraseDino(x, y);
}

void RenderManager::moveDinoLeft(int jump, int x, int y) {
    char block = 219;
    ConsoleManeger::colorPrint(x, y, DINO_COLOR, GRASS_COLOR, "%c%c%c%c%c%c%c%c         ",
        block, block, block, block, block, block, block, block);

    ConsoleManeger::colorPrint(x, y + 1, DINO_COLOR, GRASS_COLOR, "%c%c", block, block);
    ConsoleManeger::colorPrint(x + 2, y + 1, 4, GRASS_COLOR, "%c", block);
    ConsoleManeger::colorPrint(x + 3, y + 1, DINO_COLOR, GRASS_COLOR, "%c%c%c%c%c         ",
        block, block, block, block, block);

    ConsoleManeger::colorPrint(x, y + 2, DINO_COLOR, GRASS_COLOR, " %c%c%c%c%c%c%c         ",
        block, block, block, block, block, block, block);

    ConsoleManeger::colorPrint(x, y + 3, DINO_COLOR, GRASS_COLOR, " %c%c%c%c%c%c%c%c      %c ",
        block, block, block, block, block, block, block, block, block);

    ConsoleManeger::colorPrint(x, y + 4, DINO_COLOR, GRASS_COLOR, " %c%c%c%c%c%c%c%c%c%c%c%c%c  ",
        block, block, block, block, block, block, block, block, block, block, block, block, block);

    ConsoleManeger::colorPrint(x, y + 5, DINO_COLOR, GRASS_COLOR, " %c  %c%c%c%c%c%c%c%c%c%c%c%c",
        block, block, block, block, block, block, block, block, block, block, block, block, block);

    ConsoleManeger::colorPrint(x, y + 6, DINO_COLOR, GRASS_COLOR, "     %c%c%c%c%c%c%c%c%c   ",
        block, block, block, block, block, block, block, block, block);

    ConsoleManeger::colorPrint(x, y + 7, DINO_COLOR, GRASS_COLOR, "       %c%c %c%c%c    ",
        block, block, block, block, block);

    ConsoleManeger::colorPrint(x, y + 8, DINO_COLOR, GRASS_COLOR, "      %c%c   %c%c    ",
        block, block, block, block);

    ConsoleManeger::delay(speed);
    eraseDino(x, y);
}

static const char* HELICOPTER_FRAMES[] = {
    "------+------",
    " -----+-----",
    "  ----+----",
    "   ---+---",
    "    --+--",
    "     -+-",
    "      +",
    "     -+-",
    "    --+--",
    "   ---+---",
    "  ----+----",
    " -----+-----",
    "------+------"
};

void RenderManager::moveHelicopter(int x, int y) {

    RenderManager::eraseHelicopter(x, y);

    // Hélice
    ConsoleManeger::colorPrint(x + 3, y, 4, SKY_COLOR, "%s", HELICOPTER_FRAMES[posicaoHelice]);
    posicaoHelice = (posicaoHelice < 12 ? posicaoHelice + 1 : 0);

    // Corpo do helicóptero
    ConsoleManeger::colorPrint(x + 7, y + 1, 4, SKY_COLOR, "  +  ");
    ConsoleManeger::colorPrint(x + 7, y + 2, 4, SKY_COLOR, "+++++");
    ConsoleManeger::colorPrint(x, y + 3, 4, SKY_COLOR, "+     ++++++++");
    ConsoleManeger::colorPrint(x, y + 4, 4, SKY_COLOR, "++++++++++++++");
    ConsoleManeger::colorPrint(x, y + 5, 4, SKY_COLOR, "      ++++++++");
    ConsoleManeger::colorPrint(x, y + 6, 4, SKY_COLOR, "         +");
    ConsoleManeger::colorPrint(x, y + 7, 4, SKY_COLOR, "    +++++++++++");
}

void RenderManager::eraseHelicopter(int x, int y) {

    // Apaga uma área maior para cobrir todo o helicóptero
    for (int i = 0; i <= 7; i++) {
        ConsoleManeger::colorPrint(x - 2, y + i, SKY_COLOR, SKY_COLOR, "                      ");
    }
}

void RenderManager::moveTruckLeft(int x, int y) {
    char block = 219;

    // Desenha a cabine do caminhão
    ConsoleManeger::setColor(8, SKY_COLOR);
    ConsoleManeger::print(x + 1, y - 3, "%c%c%c", block, block, block);
    ConsoleManeger::print(x + 1, y - 2, "%c %c", block, block);
    ConsoleManeger::print(x, y - 1, "%c%c%c%c", block, block, block, block);
    ConsoleManeger::print(x, y, "%c%c%c%c%c%c%c%c%c%c%c%c",
        block, block, 'O', block, block, block, block, block, block, block, 'O', block);

    // Desenha a carroceria
    ConsoleManeger::setColor(10, SKY_COLOR);
    for (int i = 0; i < 4; i++) {
        ConsoleManeger::print(x + 4, y - 4 + i, "%c%c%c%c%c%c%c%c",
            block, block, block, block, block, block, block, block);
    }
}

void RenderManager::eraseTruckRight(int x, int y) {
    ConsoleManeger::setColor(SKY_COLOR, SKY_COLOR);

    // Apaga a cabine
    ConsoleManeger::print(x + 1, y - 3, "   ");
    ConsoleManeger::print(x + 1, y - 2, "   ");
    ConsoleManeger::print(x, y - 1, "    ");
    ConsoleManeger::print(x, y, "            ");

    // Apaga a carroceria
    for (int i = 0; i < 4; i++) {
        ConsoleManeger::print(x + 4, y - 4 + i, "        ");
    }
}

void RenderManager::moveTruckRight(int x, int y) {
    char block = 219;

    // Desenha a cabine 
    ConsoleManeger::setColor(8, SKY_COLOR);
    ConsoleManeger::print(x + 8, y - 3, "%c%c%c", block, block, block);
    ConsoleManeger::print(x + 8, y - 2, "%c %c", block, block);
    ConsoleManeger::print(x + 8, y - 1, "%c%c%c%c", block, block, block, block);
    ConsoleManeger::print(x, y, "%c%c%c%c%c%c%c%c%c%c%c%c",
        block, 'O', block, block, block, block, block, block, block, block, 'O', block);

    // Desenha a carroceria
    ConsoleManeger::setColor(10, SKY_COLOR);
    for (int i = 0; i < 4; i++) {
        ConsoleManeger::print(x, y - 4 + i, "%c%c%c%c%c%c%c%c",
            block, block, block, block, block, block, block, block);
    }
}

void RenderManager::eraseTruckLeft(int x, int y) {
    ConsoleManeger::setColor(SKY_COLOR, SKY_COLOR);

    // Apaga a cabine
    ConsoleManeger::print(x + 8, y - 3, "   ");
    ConsoleManeger::print(x + 8, y - 2, "   ");
    ConsoleManeger::print(x + 8, y - 1, "    ");
    ConsoleManeger::print(x, y, "            ");

    // Apaga a carroceria
    for (int i = 0; i < 4; i++) {
        ConsoleManeger::print(x, y - 4 + i, "        ");
    }
}
void RenderManager::moveMissileRight(int x, int y) {
    // Move o míssil da esquerda para a direita
    for (; x < 328; x++) {
        ConsoleManeger::setColor(4, 4);
        ConsoleManeger::print(x, y, "■");
        ConsoleManeger::delay(10);
        // Apaga a posição anterior usando a cor do céu
        ConsoleManeger::setColor(SKY_COLOR, SKY_COLOR);
        ConsoleManeger::print(x, y, " ");
    }
}

void RenderManager::moveMissileLeft(int x, int y) {
    // Move o míssil da direita para a esquerda
    for (; x >= 0; x--) {
        ConsoleManeger::setColor(4, 4);
        ConsoleManeger::print(x, y, "■");
        ConsoleManeger::delay(10);
        ConsoleManeger::setColor(SKY_COLOR, SKY_COLOR);
        ConsoleManeger::print(x, y, " ");
    }
}