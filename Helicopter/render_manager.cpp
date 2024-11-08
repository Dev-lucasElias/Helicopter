﻿#include "render_manager.h"
#include "console_maneger.h"
#include "game.h"
using namespace std;

int t, speed = 40;
void RenderManager::drawScene() {
    char block = 219;
    int skyHeight = SCREEN_HEIGHT * 2 / 3;

    // Primeiro desenha todo o céu
    ConsoleManeger::setColor(SKY_COLOR, SKY_COLOR);
    for (int y = 0; y < skyHeight; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            ConsoleManeger::gotoxy(x, y);
            cout << block;
        }
    }

    // Depois desenha toda a grama
    ConsoleManeger::setColor(GRASS_COLOR, GRASS_COLOR);
    for (int y = skyHeight; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            ConsoleManeger::gotoxy(x, y);
            cout << block;
        }
    }

    ConsoleManeger::setColor(7, 0);
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
    ConsoleManeger::setColor(11, 10);
    ConsoleManeger::gotoxy(x + 4, y + 12); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);

    // Desenhar a porta em marrom
    ConsoleManeger::setColor(6, 0); // Marrom no fundo preto
    ConsoleManeger::gotoxy(x + 8, y + 10); printf("%c%c", 219, 219);
    ConsoleManeger::gotoxy(x + 8, y + 11); printf("%c%c", 219, 219);
}

void RenderManager::eraseDino(int jump, int x, int y) {
    static int a = 1;
    ConsoleManeger::setColor(DINO_COLOR, SKY_COLOR);
    if (jump == 0)
        t = 0;
    else if (jump == 2)
        t--;
    else t++;
    ConsoleManeger::gotoxy(x, y + 15 - t);
    ConsoleManeger::gotoxy(x, y + 16 - t);
    printf("                 ");
    ConsoleManeger::gotoxy(x, y + 17 - t);
    printf("                 ");
    ConsoleManeger::gotoxy(x, y + 18 - t);
    printf("                 ");
    ConsoleManeger::gotoxy(x, y + 19 - t);
    printf("                 ");
    ConsoleManeger::gotoxy(x, y + 20 - t);
    printf("                 ");
    ConsoleManeger::gotoxy(x, y + 21 - t);
    printf("                 ");
    ConsoleManeger::gotoxy(x, y + 22 - t);
    printf("                 ");
    ConsoleManeger::gotoxy(x, y + 23 - t);
    if (jump == 1 || jump == 2) {
        printf("                 ");
        ConsoleManeger::gotoxy(x, y + 24 - t);
        printf("                 ");
    }
    else
        if (a == 1) {
            printf("                 ");
            ConsoleManeger::gotoxy(x, y + 24 - t);
            printf("                 ");
            a = 2;
        }
        else
            if (a == 2) {
                printf("                 ");
                ConsoleManeger::gotoxy(x, y + 24 - t);
                printf("                 ");
                a = 1;
            }
    ConsoleManeger::gotoxy(x, y + 25 - t);
    if (jump != 0) {
        printf("                ");
    }
}

void RenderManager::moveDinoRight(int jump, int x, int y) {
    static int a = 1;
    ConsoleManeger::setColor(DINO_COLOR, SKY_COLOR);
    if (jump == 0)
        t = 0;
    else if (jump == 2)
        t--;
    else t++;
    ConsoleManeger::gotoxy(x, y + 15 - t);
    ConsoleManeger::gotoxy(x, y + 16 - t);
    printf("         ��������");
    ConsoleManeger::gotoxy(x, y + 17 - t);
    printf("         ��������");
    ConsoleManeger::gotoxy(x, y + 18 - t);
    printf("         ��������");
    ConsoleManeger::gotoxy(x, y + 19 - t);
    printf(" �      �������� ");
    ConsoleManeger::gotoxy(x, y + 20 - t);
    printf(" ���  ���������� ");
    ConsoleManeger::gotoxy(x, y + 21 - t);
    printf(" ������������  � ");
    ConsoleManeger::gotoxy(x, y + 22 - t);
    printf("   ���������     ");
    ConsoleManeger::gotoxy(x, y + 23 - t);
    if (jump == 1 || jump == 2) {
        printf("    ��� ��       ");
        ConsoleManeger::gotoxy(x, y + 24 - t);
        printf("    ��   ��      ");
    }
    else
        if (a == 1) {
            printf("    ����  ���    ");
            ConsoleManeger::gotoxy(x, y + 24 - t);
            printf("      ��         ");
            a = 2;
        }
        else
            if (a == 2) {
                printf("     ��� ��      ");
                ConsoleManeger::gotoxy(x, y + 24 - t);
                printf("          ��     ");
                a = 1;
            }
    ConsoleManeger::gotoxy(x, y + 25 - t);
    if (jump != 0) {
        printf("                ");
    }
    ConsoleManeger::delay(speed);
    RenderManager::eraseDino(jump, x, y);
}

void RenderManager::moveDinoLeft(int jump, int x, int y) {
    static int a = 1;
    ConsoleManeger::setColor(DINO_COLOR, SKY_COLOR);
    if (jump == 0)
        t = 0;
    else if (jump == 2)
        t--;
    else t++;

    ConsoleManeger::gotoxy(x, y + 15 - t);
    printf("                 ");
    ConsoleManeger::gotoxy(x, y + 16 - t);
    printf(" �������         ");
    ConsoleManeger::gotoxy(x, y + 17 - t);
    printf(" ��������        ");
    ConsoleManeger::gotoxy(x, y + 18 - t);
    printf(" ��������        ");
    ConsoleManeger::gotoxy(x, y + 19 - t);
    printf("  ��������      �");
    ConsoleManeger::gotoxy(x, y + 20 - t);
    printf(" ������������  ��");
    ConsoleManeger::gotoxy(x, y + 21 - t);
    printf(" �  �������������");
    ConsoleManeger::gotoxy(x, y + 22 - t);
    printf("     ����������  ");
    ConsoleManeger::gotoxy(x, y + 23 - t);

    if (jump == 1 || jump == 2) {
        printf("       �� ���    ");
        ConsoleManeger::gotoxy(x, y + 24 - t);
        printf("      ��   ��    ");
    }
    else if (a == 1) {
        printf("    ���  ����    ");
        ConsoleManeger::gotoxy(x, y + 24 - t);
        printf("         ��      ");
        a = 2;
    }
    else if (a == 2) {
        printf("      �� ���     ");
        ConsoleManeger::gotoxy(x, y + 24 - t);
        printf("     ��           ");
        a = 1;
    }

    ConsoleManeger::gotoxy(x, y + 25 - t);
    if (jump != 0) {
        printf("                ");
    }

    ConsoleManeger::delay(speed);
    RenderManager::eraseDino(jump, x, y);
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
    ConsoleManeger::gotoxy(x + 3, y);
    ConsoleManeger::setColor(4, SKY_COLOR); // 2 = Verde, 1 = Azul
    switch (posicaoHelice) {
    case 0: printf("______�______\n"); break;
    case 1: printf(" _____�_____ \n"); break;
    case 2: printf("  ____�____  \n"); break;
    case 3: printf("   ___�___   \n"); break;
    case 4: printf("    __�__    \n"); break;
    case 5: printf("     _�_    \n"); break;
    case 6: printf("    __�__    \n"); break;
    case 7: printf("   ___�___   \n"); break;
    case 8: printf("  ____�____  \n"); break;
    case 9: printf(" _____�_____ \n"); break;
    case 10: printf("______�______\n"); break;
    }
    posicaoHelice = (posicaoHelice < 10 ? posicaoHelice + 1 : 1);
    ConsoleManeger::gotoxy(x + 7, y + 1);
    printf("  �  \n");
    ConsoleManeger::gotoxy(x + 7, y + 2);
    printf("�����\n");
    ConsoleManeger::gotoxy(x, y + 3);
    printf("�     ��������\n");
    ConsoleManeger::gotoxy(x, y + 4);
    printf("���������������\n");
    ConsoleManeger::gotoxy(x, y + 5);
    printf("      ��������\n");
    ConsoleManeger::gotoxy(x, y + 6);
    printf("         �\n");
    ConsoleManeger::gotoxy(x, y + 7);
    printf("    �����������\n");
    if (rand() % 30 == 7) {
        RenderManager::moveMissileRight(x + 15, y + 4);
    }
}
void RenderManager::moveHelicopterLeft(int x, int y) {
    ConsoleManeger::gotoxy(x - 2, y);
    ConsoleManeger::setColor(4, SKY_COLOR); // 2 = Verde, 1 = Azul
    switch (posicaoHelice) {
    case 0: printf("______+______\n"); break;
    case 1: printf(" _____+_____ \n"); break;
    case 2: printf("  ____+____  \n"); break;
    case 3: printf("   ___+___   \n"); break;
    case 4: printf("    __+__    \n"); break;
    case 5: printf("     _+_    \n"); break;
    case 6: printf("    __+__    \n"); break;
    case 7: printf("   ___+___   \n"); break;
    case 8: printf("  ____+____  \n"); break;
    case 9: printf(" _____+_____ \n"); break;
    case 10: printf("______+______\n"); break;
    }
    posicaoHelice = (posicaoHelice < 10 ? posicaoHelice + 1 : 1);
    ConsoleManeger::gotoxy(x + 2, y + 1);
    printf("__|__\n");
    ConsoleManeger::gotoxy(x + 1, y + 2);
    printf("/     \\====/\\\n");
    ConsoleManeger::gotoxy(x, y + 3);
    printf("(      /\n");
    ConsoleManeger::gotoxy(x + 2, y + 4);
    printf("_+__+_       \n");
    if (rand() % 30 == 7) {
        RenderManager::moveMissileLeft(x + 15, y + 4);
    }
}
void RenderManager::eraseHelicopter(int x, int y) {
    ConsoleManeger::setColor(SKY_COLOR, SKY_COLOR); // 2 = Verde, 1 = Azul
    ConsoleManeger::gotoxy(x, y);
    printf("               \n");
    ConsoleManeger::gotoxy(x, y + 1);
    printf("               \n");
    ConsoleManeger::gotoxy(x - 1, y + 2);
    printf("               \n");
    ConsoleManeger::gotoxy(x, y + 3);
    printf("               \n");
    ConsoleManeger::gotoxy(x, y + 4);
    printf("               \n");
    ConsoleManeger::gotoxy(x, y + 5);
    printf("               \n");
    ConsoleManeger::gotoxy(x, y + 6);
    printf("               \n");
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

