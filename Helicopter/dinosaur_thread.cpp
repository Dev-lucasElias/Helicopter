// dinosaur_thread.cpp
#include "dinosaur_thread.h"
#include <thread>
#include <chrono>
#include <random>

DinosaurThread::DinosaurThread(Dinosaur& d, std::mutex& m)
    : dinosaur(d), dinoMutex(m), movementDuration(0), movementInterval(50) {}

void DinosaurThread::operator()() {
    while (GameState::isGameRunning()) {
        {
            std::lock_guard<std::mutex> lock(dinoMutex);
            moveHorizontal();
        }  // Mutex é liberado aqui

        // Decide se vai pular
        if (rand() % 100 < 30) {
            jump();  // Jump tem seu próprio gerenciamento de mutex
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(40));
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
        if (currentX < SCREEN_WIDTH - 40) {
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
    int currentY, jumpHeight;

    {
        std::lock_guard<std::mutex> lock(dinoMutex);
        currentY = dinosaur.getY();
        jumpHeight = (rand() % 3) + 2;
    }  // Libera o mutex

    // Subida
    for (int i = 0; i < jumpHeight && GameState::isGameRunning(); i++) {
        {
            std::lock_guard<std::mutex> lock(dinoMutex);
            dinosaur.setY(currentY - i);
        }  // Libera o mutex durante o sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for (int i = jumpHeight; i > 0 && GameState::isGameRunning(); i--) {
        dinosaur.setY(currentY - i + 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}