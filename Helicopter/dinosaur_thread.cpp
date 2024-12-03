// dinosaur_thread.cpp
#include "dinosaur_thread.h"
#include <thread>
#include <chrono>
#include <random>
#include <algorithm>

DinosaurThread::DinosaurThread(Dinosaur& d, std::mutex& m)
    : dinosaur(d), dinoMutex(m), movementDuration(0), movementInterval(50) {
    std::srand(std::time(nullptr));
}

void DinosaurThread::operator()() {
    while (GameState::isGameRunning()) {
        // Decidimos se vamos pular antes de adquirir qualquer lock
        bool shouldJump = (rand() % 10 == 0);

        if (shouldJump) {
            // Se for pular, não pegamos o lock aqui
            jump();
        }
        else {
            // Lock apenas para movimento horizontal
            std::lock_guard<std::mutex> lock(dinoMutex);

            // Lógica de movimento horizontal
            if (dinosaur.getDirection() == 'R') {
                if (dinosaur.getX() >= SCREEN_WIDTH - DINO_WIDTH - 40) {
                    dinosaur.setDirection('L');
                }
                else {
                    dinosaur.setX(dinosaur.getX() + DINO_SPEED);
                }
            }
            else {
                if (dinosaur.getX() <= 0) {
                    dinosaur.setDirection('R');
                }
                else {
                    dinosaur.setX(dinosaur.getX() - DINO_SPEED);
                }
            }

            // Mantém o dinossauro no nível do chão quando não está pulando
            dinosaur.setY(SCREEN_HEIGHT - DINO_HEIGHT - 1);

        }

        // Pausa comum para ambos os casos
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void DinosaurThread::moveHorizontal() {
    movementDuration++;

    if (movementDuration >= movementInterval) {
        if (rand() % 2 == 0) {
            dinosaur.setDirection(dinosaur.getDirection() == 'R' ? 'L' : 'R');
        }
        movementDuration = 0;
        movementInterval = rand() % 100 + 30;
    }

    int currentX = dinosaur.getX();
    if (dinosaur.getDirection() == 'R') {
        if (currentX < DINO_WIDTH - 40) {
            dinosaur.setX(currentX + 1);
        }
        else {
            dinosaur.setDirection('L');
        }
    }
    else {
        if (currentX > 0) {
            dinosaur.setX(currentX - 1);
        }
        else {
            dinosaur.setDirection('R');
        }
    }
}

void DinosaurThread::jump() {
    const int MIN_JUMP = 3;
    const int MAX_JUMP = 14;
    const int JUMP_HEIGHT = (rand() % (MAX_JUMP - MIN_JUMP + 1)) + MIN_JUMP;

    
    const int JUMP_SPEED = 2;  
    const int FRAME_DELAY = 16;   

    int startY = SCREEN_HEIGHT - DINO_HEIGHT - 1;
    int currentY = startY;

    // Fase de subida do pulo
    for (int y = 0; y < JUMP_HEIGHT && GameState::isGameRunning(); y += JUMP_SPEED) {
        {
            std::lock_guard<std::mutex> lock(dinoMutex);
            currentY = startY - y;
            dinosaur.setY(currentY);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DELAY));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(50 + JUMP_HEIGHT * 5));

    for (int y = JUMP_HEIGHT; y > 0 && GameState::isGameRunning(); y -= JUMP_SPEED) {
        {
            std::lock_guard<std::mutex> lock(dinoMutex);
            currentY = startY - y;
            dinosaur.setY(currentY);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DELAY));
    }

    {
        std::lock_guard<std::mutex> lock(dinoMutex);
        dinosaur.setY(startY);
    }
}