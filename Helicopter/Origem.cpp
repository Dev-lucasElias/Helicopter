/* BROUGHT TO YOU BY CODE-PROJECTS.ORG */
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <cwchar>
#include<time.h>//necess?rio p/ fun??o time()


// Define as cores
#define SKY_COLOR 1   // Azul
#define GRASS_COLOR 2 // Verde
#define DINO_COLOR 3 // Verde claro

void setConsoleSize(int width, int height) {
    char command[30];
    sprintf(command, "mode con: cols=%d lines=%d", width, height);
    system(command);
}

void setColor(int textColor, int backgroundColor) {
    // Muda a cor do texto e do fundo
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (backgroundColor << 4) | textColor);
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void delay(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void getup()
{
    system("cls");
    gotoxy(10, 2);
    printf("Press X to Exit, Press Space to Jump");
    gotoxy(62, 2);
    printf("SCORE : ");
    gotoxy(1, 25);
    for (int x = 0;x < 79;x++)
        printf("?");
}

int t, speed = 40;

void desenha_cenario(int width, int height) {
    // Define o caractere ASCII 219 (bloco s?lido)
    char block = 219;

    // Calcula a linha que separa o c?u do gramado
    int skyHeight = 100;//height * 2 / 3;

    for (int y = 0; y < height; y++) {
        // Configura cor do c?u (azul)
        if (y < skyHeight) {
            setColor(SKY_COLOR, SKY_COLOR);
        }
        // Configura cor do gramado (verde)
        else {
            setColor(GRASS_COLOR, GRASS_COLOR);
        }

        // Desenha a linha da paisagem
        for (int x = 0; x < width; x++) {
            printf("%c", block);
        }
        printf("\n");
    }

    // Reseta para cor padr?o (branco no preto)
    setColor(7, 0);
}

void desenha_deposito(int x, int y) {
    // Desenhar o teto da casa 
    setColor(4, 4); // Azul no fundo preto
    gotoxy(x + 10, y + 2); printf("    %c%c%c", 219, 219, 219);
    gotoxy(x + 9, y + 3);  printf("   %c%c%c%c%c", 219, 219, 219, 219, 219);
    gotoxy(x + 8, y + 4);  printf("  %c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219);
    gotoxy(x + 7, y + 5);  printf(" %c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
    gotoxy(x + 6, y + 6);  printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);

    // Desenhar o corpo da casa (quadrado) em amarelo
    setColor(14, 14);
    for (int i = 7; i <= 11; i++) {
        gotoxy(x + 6, y + i);  printf("%c        %c", 219, 219);
    }

    // Desenhar a base da casa (ch?o) em verde
    setColor(10, 10);
    gotoxy(x + 4, y + 12); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);

    // Desenhar a porta em marrom
    setColor(6, 0); // Marrom no fundo preto
    gotoxy(x + 8, y + 10); printf("%c%c", 219, 219);
    gotoxy(x + 8, y + 11); printf("%c%c", 219, 219);
}

void apaga_dino(int jump, int x, int y) {
    static int a = 1;
    setColor(DINO_COLOR, SKY_COLOR);
    if (jump == 0)
        t = 0;
    else if (jump == 2)
        t--;
    else t++;
    gotoxy(x, y + 15 - t);
    gotoxy(x, y + 16 - t);
    printf("                 ");
    gotoxy(x, y + 17 - t);
    printf("                 ");
    gotoxy(x, y + 18 - t);
    printf("                 ");
    gotoxy(x, y + 19 - t);
    printf("                 ");
    gotoxy(x, y + 20 - t);
    printf("                 ");
    gotoxy(x, y + 21 - t);
    printf("                 ");
    gotoxy(x, y + 22 - t);
    printf("                 ");
    gotoxy(x, y + 23 - t);
    if (jump == 1 || jump == 2) {
        printf("                 ");
        gotoxy(x, y + 24 - t);
        printf("                 ");
    }
    else
        if (a == 1) {
            printf("                 ");
            gotoxy(x, y + 24 - t);
            printf("                 ");
            a = 2;
        }
        else
            if (a == 2) {
                printf("                 ");
                gotoxy(x, y + 24 - t);
                printf("                 ");
                a = 1;
            }
    gotoxy(x, y + 25 - t);
    if (jump != 0) {
        printf("                ");
    }
}

void dinoE2D(int jump, int x, int y) {
    static int a = 1;
    setColor(DINO_COLOR, SKY_COLOR);
    if (jump == 0)
        t = 0;
    else if (jump == 2)
        t--;
    else t++;
    gotoxy(x, y + 15 - t);
    gotoxy(x, y + 16 - t);
    printf("         ????????");
    gotoxy(x, y + 17 - t);
    printf("         ????????");
    gotoxy(x, y + 18 - t);
    printf("         ????????");
    gotoxy(x, y + 19 - t);
    printf(" ?      ???????? ");
    gotoxy(x, y + 20 - t);
    printf(" ???  ?????????? ");
    gotoxy(x, y + 21 - t);
    printf(" ????????????  ? ");
    gotoxy(x, y + 22 - t);
    printf("   ?????????     ");
    gotoxy(x, y + 23 - t);
    if (jump == 1 || jump == 2) {
        printf("    ??? ??       ");
        gotoxy(x, y + 24 - t);
        printf("    ??   ??      ");
    }
    else
        if (a == 1) {
            printf("    ????  ???    ");
            gotoxy(x, y + 24 - t);
            printf("      ??         ");
            a = 2;
        }
        else
            if (a == 2) {
                printf("     ??? ??      ");
                gotoxy(x, y + 24 - t);
                printf("          ??     ");
                a = 1;
            }
    gotoxy(x, y + 25 - t);
    if (jump != 0) {
        printf("                ");
    }
    delay(speed);
    apaga_dino(jump, x, y);
}

void dinoD2E(int jump, int x, int y) {
    static int a = 1;
    setColor(DINO_COLOR, SKY_COLOR);
    if (jump == 0)
        t = 0;
    else if (jump == 2)
        t--;
    else t++;

    gotoxy(x, y + 15 - t);
    printf("                 ");
    gotoxy(x, y + 16 - t);
    printf(" ???????         ");
    gotoxy(x, y + 17 - t);
    printf(" ????????        ");
    gotoxy(x, y + 18 - t);
    printf(" ????????        ");
    gotoxy(x, y + 19 - t);
    printf("  ????????      ?");
    gotoxy(x, y + 20 - t);
    printf(" ????????????  ??");
    gotoxy(x, y + 21 - t);
    printf(" ?  ?????????????");
    gotoxy(x, y + 22 - t);
    printf("     ??????????  ");
    gotoxy(x, y + 23 - t);

    if (jump == 1 || jump == 2) {
        printf("       ?? ???    ");
        gotoxy(x, y + 24 - t);
        printf("      ??   ??    ");
    }
    else if (a == 1) {
        printf("    ???  ????    ");
        gotoxy(x, y + 24 - t);
        printf("         ??      ");
        a = 2;
    }
    else if (a == 2) {
        printf("      ?? ???     ");
        gotoxy(x, y + 24 - t);
        printf("     ??           ");
        a = 1;
    }

    gotoxy(x, y + 25 - t);
    if (jump != 0) {
        printf("                ");
    }

    delay(speed);
    apaga_dino(jump, x, y);
}

int posicaoHelice = 0;


void disparaE2D(int x, int y) {
    for (; x < 328; x++) {
        gotoxy(x, y);
        setColor(4, 4);
        printf("?");
        delay(10);
        gotoxy(x, y);
        setColor(SKY_COLOR, SKY_COLOR);
        printf(" ");
    }
}

void disparaD2E(int x, int y) {
    for (; x >= 0; x--) {
        gotoxy(x, y);
        setColor(4, 4);
        printf("?");
        delay(10);
        gotoxy(x, y);
        setColor(SKY_COLOR, SKY_COLOR);
        printf(" ");
    }
}

void helicopteroE2D(int x, int y) {
    gotoxy(x + 3, y);
    setColor(4, SKY_COLOR); // 2 = Verde, 1 = Azul
    switch (posicaoHelice) {
    case 0: printf("______?______\n"); break;
    case 1: printf(" _____?_____ \n"); break;
    case 2: printf("  ____?____  \n"); break;
    case 3: printf("   ___?___   \n"); break;
    case 4: printf("    __?__    \n"); break;
    case 5: printf("     _?_    \n"); break;
    case 6: printf("    __?__    \n"); break;
    case 7: printf("   ___?___   \n"); break;
    case 8: printf("  ____?____  \n"); break;
    case 9: printf(" _____?_____ \n"); break;
    case 10: printf("______?______\n"); break;
    }
    posicaoHelice = (posicaoHelice < 10 ? posicaoHelice + 1 : 1);
    gotoxy(x + 7, y + 1);
    printf("  ?  \n");
    gotoxy(x + 7, y + 2);
    printf("?????\n");
    gotoxy(x, y + 3);
    printf("?     ????????\n");
    gotoxy(x, y + 4);
    printf("???????????????\n");
    gotoxy(x, y + 5);
    printf("      ????????\n");
    gotoxy(x, y + 6);
    printf("         ?\n");
    gotoxy(x, y + 7);
    printf("    ???????????\n");
    if (rand() % 30 == 7) {
        disparaE2D(x + 15, y + 4);
    }
}
void helicopteroD2E(int x, int y) {
    gotoxy(x - 2, y);
    setColor(4, SKY_COLOR); // 2 = Verde, 1 = Azul
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
    gotoxy(x + 2, y + 1);
    printf("__|__\n");
    gotoxy(x + 1, y + 2);
    printf("/     \\====/\\\n");
    gotoxy(x, y + 3);
    printf("(      /\n");
    gotoxy(x + 2, y + 4);
    printf("_+__+_       \n");
    if (rand() % 30 == 7) {
        disparaD2E(x + 15, y + 4);
    }
}
void apaga_helicopteroE2D(int x, int y) {
    setColor(SKY_COLOR, SKY_COLOR); // 2 = Verde, 1 = Azul
    gotoxy(x, y);
    printf("               \n");
    gotoxy(x, y + 1);
    printf("               \n");
    gotoxy(x - 1, y + 2);
    printf("               \n");
    gotoxy(x, y + 3);
    printf("               \n");
    gotoxy(x, y + 4);
    printf("               \n");
    gotoxy(x, y + 5);
    printf("               \n");
    gotoxy(x, y + 6);
    printf("               \n");
}

void desenha_caminhaoD2E(int x, int y) {
    // Desenhar cavalinho
    setColor(8, SKY_COLOR);
    gotoxy(x + 1, y - 3); printf("%c%c%c", 219, 219, 219);
    gotoxy(x + 1, y - 2); printf("%c%c%c%", 219, ' ', 219);
    gotoxy(x, y - 1); printf("%c%c%c%c", 219, 219, 219, 219);
    gotoxy(x, y); printf("%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 'O', 219, 219, 219, 219, 219, 219, 219, 'O', 219);
    setColor(10, SKY_COLOR);
    // Desenhar a parte do caminh?o (carroceria)
    gotoxy(x + 4, y - 4); printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219);
    gotoxy(x + 4, y - 3); printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219);
    gotoxy(x + 4, y - 2); printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219);
    gotoxy(x + 4, y - 1); printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219);
}
void apaga_caminhaoD2E(int x, int y) {
    // Apagar cavalinho
    setColor(SKY_COLOR, SKY_COLOR);
    gotoxy(x + 1, y - 3); printf("%c%c%c", ' ', ' ', ' ');
    gotoxy(x + 1, y - 2); printf("%c%c%c%", ' ', ' ', ' ');
    gotoxy(x, y - 1); printf("%c%c%c%c", ' ', ' ', ' ', ' ');
    gotoxy(x, y); printf("%c%c%c%c%c%c%c%c%c%c%c%c", ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    setColor(SKY_COLOR, SKY_COLOR);
    // Apagar carroceria
    gotoxy(x + 4, y - 4); printf("%c%c%c%c%c%c%c%c", ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    gotoxy(x + 4, y - 3); printf("%c%c%c%c%c%c%c%c", ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    gotoxy(x + 4, y - 2); printf("%c%c%c%c%c%c%c%c", ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    gotoxy(x + 4, y - 1); printf("%c%c%c%c%c%c%c%c", ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
}

void desenha_caminhaoE2D(int x, int y) {
    // Desenhar cavalinho 
    setColor(8, SKY_COLOR);
    gotoxy(x + 8, y - 3); printf("%c%c%c", 219, 219, 219);
    gotoxy(x + 8, y - 2); printf("%c%c%c", 219, ' ', 219);
    gotoxy(x + 8, y - 1); printf("%c%c%c%c", 219, 219, 219, 219);
    gotoxy(x, y); printf("%c%c%c%c%c%c%c%c%c%c%c%c", 219, 'O', 219, 219, 219, 219, 219, 219, 219, 219, 'O', 219);

    // Desenhar a carroceria
    setColor(10, SKY_COLOR);
    gotoxy(x, y - 4); printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219);
    gotoxy(x, y - 3); printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219);
    gotoxy(x, y - 2); printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219);
    gotoxy(x, y - 1); printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219);
}

void apaga_caminhaoE2D(int x, int y) {
    // apaga cavalinho 
    setColor(SKY_COLOR, SKY_COLOR);
    gotoxy(x + 8, y - 3); printf("%c%c%c", ' ', ' ', ' ');
    gotoxy(x + 8, y - 2); printf("%c%c%c", ' ', ' ', ' ');
    gotoxy(x + 8, y - 1); printf("%c%c%c%c", ' ', ' ', ' ', ' ');
    gotoxy(x, y); printf("%c%c%c%c%c%c%c%c%c%c%c%c", ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

    // Apaga carroceria
    setColor(SKY_COLOR, SKY_COLOR);
    gotoxy(x, y - 4); printf("%c%c%c%c%c%c%c%c", ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    gotoxy(x, y - 3); printf("%c%c%c%c%c%c%c%c", ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    gotoxy(x, y - 2); printf("%c%c%c%c%c%c%c%c", ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    gotoxy(x, y - 1); printf("%c%c%c%c%c%c%c%c", ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
}
int main() {
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Largura dos caracteres
    cfi.dwFontSize.Y = 12;                  // Altura
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    system("mode con: lines=116 cols=328");
    char ch;
    int i, frente = true, x, coluna;
    getup();
    desenha_cenario(328, 116);
    desenha_deposito(200, 86);
    srand(time(NULL));
    while (true) {
        for (coluna = 0; coluna < 300; coluna++) {
            helicopteroE2D(coluna, 75);
            delay(10);
            apaga_helicopteroE2D(coluna, 75);
        }
        for (coluna = 300; coluna > 218; coluna--) {
            desenha_caminhaoD2E(coluna, 98);
            delay(100);
            apaga_caminhaoD2E(coluna, 98);
        }
        for (coluna = 218; coluna <= 300; coluna++) {
            desenha_caminhaoE2D(coluna, 98);
            delay(100);
            apaga_caminhaoE2D(coluna, 98);
        }

        while (true) {
            if (frente) {
                dinoE2D(rand() % 2, x, 74);x++;
            }
            if (x == 140) frente = false;
            if (!frente) {
                dinoD2E(rand() % 2, x, 74);
                x--;
            }
            if (x == 2) frente = true;
        }
    }
}
