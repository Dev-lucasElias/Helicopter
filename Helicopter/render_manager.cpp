#include "render_manager.h"
#include "console_maneger.h"
#include "game.h"
using namespace std;

int t, speed = 40;
void RenderManager::drawScene(int startX, int startY, int endX, int endY) {
    char block = 219;
    int skyHeight = SCREEN_HEIGHT * 2 / 3;

    // Limita as coordenadas aos limites da tela
    startX = max(0, startX);
    startY = max(0, startY);
    endX = min(SCREEN_WIDTH, endX);
    endY = min(SCREEN_HEIGHT, endY);

    // Desenha o céu
    ConsoleManeger::setColor(SKY_COLOR, SKY_COLOR);
    for (int y = startY; y < min(skyHeight, endY); y++) {
        for (int x = startX; x < endX; x++) {
            ConsoleManeger::gotoxy(x, y);
            cout << block;
        }
    }

    // Desenha a grama
    ConsoleManeger::setColor(GRASS_COLOR, GRASS_COLOR);
    for (int y = max(skyHeight, startY); y < endY; y++) {
        for (int x = startX; x < endX; x++) {
            ConsoleManeger::gotoxy(x, y);
            cout << block;
        }
    }

    ConsoleManeger::setColor(7, 0);
}

// Sobrecarga para redesenhar toda a tela
void RenderManager::drawScene() {
    drawScene(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}


void RenderManager::drawDepot(int x, int y) {
    // Desenhar o teto da casa 
    ConsoleManeger::setColor(4, 4); // Azul no fundo preto
    ConsoleManeger::gotoxy(x + 10, y + 2); printf("    %c%c%c", 219, 219, 219);
    ConsoleManeger::gotoxy(x + 9, y + 3);  printf("   %c%c%c%c%c", 219, 219, 219, 219, 219);
    ConsoleManeger::gotoxy(x + 8, y + 4);  printf("  %c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219);
    ConsoleManeger::gotoxy(x + 7, y + 5);  printf(" %c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
    ConsoleManeger::gotoxy(x + 6, y + 6);  printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);

    // Desenhar o corpo da casa (quadrado) em amarelo
    ConsoleManeger::setColor(14, 14);
    for (int i = 7; i <= 11; i++) {
        ConsoleManeger::gotoxy(x + 6, y + i);  printf("%c         %c", 219, 219);
    }

    // Desenhar a base da casa (ch�o) em verde
    ConsoleManeger::setColor(15, 13);
    ConsoleManeger::gotoxy(x - 5, y + 12); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);

    // Desenhar a porta em marrom
    ConsoleManeger::setColor(6, 0); // Marrom no fundo preto
    ConsoleManeger::gotoxy(x + 8, y + 9); printf("%c%c", 219, 219);
    ConsoleManeger::gotoxy(x + 8, y + 10); printf("%c%c", 219, 219);
}

void RenderManager::drawDino(int x, int y) {
    char block = 219;  // Bloco sólido

    // Define cores
    ConsoleManeger::setColor(DINO_COLOR, GRASS_COLOR);  // Cor principal do dino

    // Desenha o corpo do dinossauro
    ConsoleManeger::gotoxy(x, y);
    printf("         %c%c%c%c%c%c%c%c", block, block, block, block, block, block, block, block); // Cabeça

    ConsoleManeger::gotoxy(x, y + 1);
    printf("         %c%c", block, block);
    ConsoleManeger::setColor(4, GRASS_COLOR);  // Cor do olho (vermelho)
    printf("%c", block);
    ConsoleManeger::setColor(DINO_COLOR, GRASS_COLOR);  // Volta cor principal
    printf("%c%c%c%c%c", block, block, block, block, block); // Resto da cabeça

    ConsoleManeger::gotoxy(x, y + 2);
    printf("         %c%c%c%c%c%c%c ", block, block, block, block, block, block, block); // Pescoço

    ConsoleManeger::gotoxy(x, y + 3);
    printf(" %c      %c%c%c%c%c%c%c%c ", block, block, block, block, block, block, block, block, block); // Corpo superior

    ConsoleManeger::gotoxy(x, y + 4);
    printf(" %c%c%c  %c%c%c%c%c%c%c%c%c%c ", block, block, block, block, block, block, block, block, block, block, block, block, block); // Corpo meio

    ConsoleManeger::gotoxy(x, y + 5);
    printf(" %c%c%c%c%c%c%c%c%c%c%c%c  %c ", block, block, block, block, block, block, block, block, block, block, block, block, block); // Corpo inferior

    ConsoleManeger::gotoxy(x, y + 6);
    printf("   %c%c%c%c%c%c%c%c%c     ", block, block, block, block, block, block, block, block, block); // Cauda superior

    ConsoleManeger::gotoxy(x, y + 7);
    printf("    %c%c%c %c%c       ", block, block, block, block, block); // Perna superior

    ConsoleManeger::gotoxy(x, y + 8);
    printf("    %c%c   %c%c      ", block, block, block, block); // Perna inferior

    ConsoleManeger::setColor(7, 0);  // Restaura cores padrão
}

void RenderManager::eraseDino(int x, int y) {
    int skyHeight = SCREEN_HEIGHT * 2 / 3;
    char block = 219;

    // Para cada linha do dinossauro
    for (int i = 0; i <= 8; i++) {
        ConsoleManeger::gotoxy(x, y + i);

        // Determina a cor baseada na posição vertical atual
        if (y + i >= skyHeight) {
            ConsoleManeger::setColor(GRASS_COLOR, GRASS_COLOR);
        }
        else {
            ConsoleManeger::setColor(SKY_COLOR, SKY_COLOR);
        }

        printf("                 ");  // 17 espaços
    }

    ConsoleManeger::setColor(7, 0);
}

void RenderManager::moveDinoRight(int jump, int x, int y) {
    char block = 219;

    ConsoleManeger::setColor(DINO_COLOR, GRASS_COLOR);

    // Cabeça
    ConsoleManeger::gotoxy(x, y);
    printf("         %c%c%c%c%c%c%c%c", block, block, block, block, block, block, block, block);

    // Cabeça com olho
    ConsoleManeger::gotoxy(x, y + 1);
    printf("         %c%c", block, block);
    ConsoleManeger::setColor(4, GRASS_COLOR);  // Olho vermelho
    printf("%c", block);
    ConsoleManeger::setColor(DINO_COLOR, GRASS_COLOR);
    printf("%c%c%c%c%c", block, block, block, block, block);

    // Pescoço
    ConsoleManeger::gotoxy(x, y + 2);
    printf("         %c%c%c%c%c%c%c ", block, block, block, block, block, block, block);

    // Corpo superior
    ConsoleManeger::gotoxy(x, y + 3);
    printf(" %c      %c%c%c%c%c%c%c%c ", block, block, block, block, block, block, block, block, block);

    // Corpo meio
    ConsoleManeger::gotoxy(x, y + 4);
    printf(" %c%c%c  %c%c%c%c%c%c%c%c%c%c ", block, block, block, block, block, block, block, block, block, block, block, block, block);

    // Corpo inferior
    ConsoleManeger::gotoxy(x, y + 5);
    printf(" %c%c%c%c%c%c%c%c%c%c%c%c  %c ", block, block, block, block, block, block, block, block, block, block, block, block, block);

    // Cauda
    ConsoleManeger::gotoxy(x, y + 6);
    printf("   %c%c%c%c%c%c%c%c%c     ", block, block, block, block, block, block, block, block, block);

    // Perna superior
    ConsoleManeger::gotoxy(x, y + 7);
    printf("    %c%c%c %c%c       ", block, block, block, block, block);

    // Perna inferior
    ConsoleManeger::gotoxy(x, y + 8);
    printf("    %c%c   %c%c      ", block, block, block, block);

    ConsoleManeger::setColor(7, 0);
    ConsoleManeger::delay(speed);
    RenderManager::eraseDino(x, y);

}

void RenderManager::moveDinoLeft(int jump, int x, int y) {
    char block = 219;

    ConsoleManeger::setColor(DINO_COLOR, GRASS_COLOR);

    // Cabeça
    ConsoleManeger::gotoxy(x, y);
    printf("%c%c%c%c%c%c%c%c         ", block, block, block, block, block, block, block, block);

    // Cabeça com olho
    ConsoleManeger::gotoxy(x, y + 1);
    printf("%c%c", block, block);
    ConsoleManeger::setColor(4, GRASS_COLOR);  // Olho vermelho
    printf("%c", block);
    ConsoleManeger::setColor(DINO_COLOR, GRASS_COLOR);
    printf("%c%c%c%c%c         ", block, block, block, block, block);

    // Pescoço
    ConsoleManeger::gotoxy(x, y + 2);
    printf(" %c%c%c%c%c%c%c         ", block, block, block, block, block, block, block);

    // Corpo superior
    ConsoleManeger::gotoxy(x, y + 3);
    printf(" %c%c%c%c%c%c%c%c      %c ", block, block, block, block, block, block, block, block, block);

    // Corpo meio
    ConsoleManeger::gotoxy(x, y + 4);
    printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c  ", block, block, block, block, block, block, block, block, block, block, block, block, block);

    // Corpo inferior
    ConsoleManeger::gotoxy(x, y + 5);
    printf(" %c  %c%c%c%c%c%c%c%c%c%c%c%c", block, block, block, block, block, block, block, block, block, block, block, block, block);

    // Cauda
    ConsoleManeger::gotoxy(x, y + 6);
    printf("     %c%c%c%c%c%c%c%c%c   ", block, block, block, block, block, block, block, block, block);

    // Perna superior
    ConsoleManeger::gotoxy(x, y + 7);
    printf("       %c%c %c%c%c    ", block, block, block, block, block);

    // Perna inferior
    ConsoleManeger::gotoxy(x, y + 8);
    printf("      %c%c   %c%c    ", block, block, block, block);

    ConsoleManeger::setColor(7, 0);
    ConsoleManeger::delay(speed);
    RenderManager::eraseDino(x, y);
}

int posicaoHelice = 0;


void RenderManager::moveMissileRight(int x, int y) {
    for (; x < 328; x++) {
        ConsoleManeger::gotoxy(x, y);
        ConsoleManeger::setColor(4, 4);
        printf("�");
        ConsoleManeger::delay(10);
        ConsoleManeger::gotoxy(x, y);
        ConsoleManeger::setColor(SKY_COLOR, SKY_COLOR);
        printf(" ");
    }
}

void RenderManager::moveMissileLeft(int x, int y) {
    for (; x >= 0; x--) {
        ConsoleManeger::gotoxy(x, y);
        ConsoleManeger::setColor(4, 4);
        printf("�");
        ConsoleManeger::delay(10);
        ConsoleManeger::gotoxy(x, y);
        ConsoleManeger::setColor(SKY_COLOR, SKY_COLOR);
        printf(" ");
    }
}

void RenderManager::moveHelicopterRight(int x, int y) {
    // Primeiro limpar a posição anterior
    eraseHelicopter(x, y);

    ConsoleManeger::setColor(4, SKY_COLOR);

    // Desenhar hélice
    ConsoleManeger::gotoxy(x + 3, y);
    switch (posicaoHelice) {
    case 0: printf("______+______"); break;
    case 1: printf(" _____+_____ "); break;
    case 2: printf("  ____+____  "); break;
    case 3: printf("   ___+___   "); break;
    case 4: printf("    __+__    "); break;
    case 5: printf("     _+_     "); break;
    case 6: printf("    __+__    "); break;
    case 7: printf("   ___+___   "); break;
    case 8: printf("  ____+____  "); break;
    case 9: printf(" _____+_____ "); break;
    case 10: printf("______+______"); break;
    }
    posicaoHelice = (posicaoHelice < 10 ? posicaoHelice + 1 : 1);

    // Desenhar corpo
    ConsoleManeger::gotoxy(x + 7, y + 1);
    printf("  +  ");
    ConsoleManeger::gotoxy(x + 7, y + 2);
    printf("+++++");
    ConsoleManeger::gotoxy(x, y + 3);
    printf("+     ++++++++");
    ConsoleManeger::gotoxy(x, y + 4);
    printf("++++++++++++++");
    ConsoleManeger::gotoxy(x, y + 5);
    printf("      ++++++++");
    ConsoleManeger::gotoxy(x, y + 6);
    printf("         +");
    ConsoleManeger::gotoxy(x, y + 7);
    printf("    +++++++++++");
}

void RenderManager::moveHelicopterLeft(int x, int y) {
    // Primeiro limpar a posição anterior
    eraseHelicopter(x, y);

    ConsoleManeger::setColor(4, SKY_COLOR);

    // Desenhar hélice
    ConsoleManeger::gotoxy(x - 2, y);
    switch (posicaoHelice) {
    case 0: printf("______+______"); break;
    case 1: printf(" _____+_____ "); break;
    case 2: printf("  ____+____  "); break;
    case 3: printf("   ___+___   "); break;
    case 4: printf("    __+__    "); break;
    case 5: printf("     _+_     "); break;
    case 6: printf("    __+__    "); break;
    case 7: printf("   ___+___   "); break;
    case 8: printf("  ____+____  "); break;
    case 9: printf(" _____+_____ "); break;
    case 10: printf("______+______"); break;
    }
    posicaoHelice = (posicaoHelice < 10 ? posicaoHelice + 1 : 1);

    ConsoleManeger::gotoxy(x + 2, y + 1);
    printf("__|__");
    ConsoleManeger::gotoxy(x + 1, y + 2);
    printf("/     \\====/\\");
    ConsoleManeger::gotoxy(x, y + 3);
    printf("(      /");
    ConsoleManeger::gotoxy(x + 2, y + 4);
    printf("_+__+_       ");
}
void RenderManager::eraseHelicopter(int x, int y) {
    ConsoleManeger::setColor(SKY_COLOR, SKY_COLOR);

    // Limpar área da hélice (mais larga que o corpo)
    ConsoleManeger::gotoxy(x - 2, y);
    printf("                      "); // 22 espaços para cobrir toda a hélice

    // Limpar corpo do helicóptero
    for (int i = 1; i <= 7; i++) {
        ConsoleManeger::gotoxy(x - 2, y + i);
        printf("                 "); // 17 espaços para cobrir o corpo
    }
}

void RenderManager::moveTruckLeft(int x, int y) {
    // Desenhar cavalinho
    ConsoleManeger::setColor(8, SKY_COLOR);
    ConsoleManeger::gotoxy(x + 1, y - 3); printf("%c%c%c", 219, 219, 219);
    ConsoleManeger::gotoxy(x + 1, y - 2); printf("%c%c%c%", 219, ' ', 219);
    ConsoleManeger::gotoxy(x, y - 1); printf("%c%c%c%c", 219, 219, 219, 219);
    ConsoleManeger::gotoxy(x, y); printf("%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 'O', 219, 219, 219, 219, 219, 219, 219, 'O', 219);
    ConsoleManeger::setColor(10, SKY_COLOR);
    // Desenhar a parte do caminh�o (carroceria)
    ConsoleManeger::gotoxy(x + 4, y - 4); printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219);
    ConsoleManeger::gotoxy(x + 4, y - 3); printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219);
    ConsoleManeger::gotoxy(x + 4, y - 2); printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219);
    ConsoleManeger::gotoxy(x + 4, y - 1); printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219);
}
void RenderManager::eraseTruckRight(int x, int y) {
    // Apagar cavalinho
    ConsoleManeger::setColor(SKY_COLOR, SKY_COLOR);
    ConsoleManeger::gotoxy(x + 1, y - 3); printf("%c%c%c", ' ', ' ', ' ');
    ConsoleManeger::gotoxy(x + 1, y - 2); printf("%c%c%c%", ' ', ' ', ' ');
    ConsoleManeger::gotoxy(x, y - 1); printf("%c%c%c%c", ' ', ' ', ' ', ' ');
    ConsoleManeger::gotoxy(x, y); printf("%c%c%c%c%c%c%c%c%c%c%c%c", ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    ConsoleManeger::setColor(SKY_COLOR, SKY_COLOR);
    // Apagar carroceria
    ConsoleManeger::gotoxy(x + 4, y - 4); printf("%c%c%c%c%c%c%c%c", ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    ConsoleManeger::gotoxy(x + 4, y - 3); printf("%c%c%c%c%c%c%c%c", ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    ConsoleManeger::gotoxy(x + 4, y - 2); printf("%c%c%c%c%c%c%c%c", ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    ConsoleManeger::gotoxy(x + 4, y - 1); printf("%c%c%c%c%c%c%c%c", ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
}

void RenderManager::moveTruckRight(int x, int y) {
    // Desenhar cavalinho 
    ConsoleManeger::setColor(8, SKY_COLOR);
    ConsoleManeger::gotoxy(x + 8, y - 3); printf("%c%c%c", 219, 219, 219);
    ConsoleManeger::gotoxy(x + 8, y - 2); printf("%c%c%c", 219, ' ', 219);
    ConsoleManeger::gotoxy(x + 8, y - 1); printf("%c%c%c%c", 219, 219, 219, 219);
    ConsoleManeger::gotoxy(x, y); printf("%c%c%c%c%c%c%c%c%c%c%c%c", 219, 'O', 219, 219, 219, 219, 219, 219, 219, 219, 'O', 219);

    // Desenhar a carroceria
    ConsoleManeger::setColor(10, SKY_COLOR);
    ConsoleManeger::gotoxy(x, y - 4); printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219);
    ConsoleManeger::gotoxy(x, y - 3); printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219);
    ConsoleManeger::gotoxy(x, y - 2); printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219);
    ConsoleManeger::gotoxy(x, y - 1); printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219);
}

void RenderManager::eraseTruckLeft(int x, int y) {
    // apaga cavalinho 
    ConsoleManeger::setColor(SKY_COLOR, SKY_COLOR);
    ConsoleManeger::gotoxy(x + 8, y - 3); printf("%c%c%c", ' ', ' ', ' ');
    ConsoleManeger::gotoxy(x + 8, y - 2); printf("%c%c%c", ' ', ' ', ' ');
    ConsoleManeger::gotoxy(x + 8, y - 1); printf("%c%c%c%c", ' ', ' ', ' ', ' ');
    ConsoleManeger::gotoxy(x, y); printf("%c%c%c%c%c%c%c%c%c%c%c%c", ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

    // Apaga carroceria
    ConsoleManeger::setColor(SKY_COLOR, SKY_COLOR);
    ConsoleManeger::gotoxy(x, y - 4); printf("%c%c%c%c%c%c%c%c", ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    ConsoleManeger::gotoxy(x, y - 3); printf("%c%c%c%c%c%c%c%c", ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    ConsoleManeger::gotoxy(x, y - 2); printf("%c%c%c%c%c%c%c%c", ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    ConsoleManeger::gotoxy(x, y - 1); printf("%c%c%c%c%c%c%c%c", ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
}

