// input_thread.cpp
#include "input_thread.h"

InputThread::InputThread(Helicopter& h, std::vector<Missile>& m, std::mutex& mm, std::mutex& hm)
    : helicopter(h), missiles(m), missileMutex(mm), helicopterMutex(hm) {}

void InputThread::operator()() {
    while (GameState::isGameRunning()) {
        if (!helicopter.getIsReloading()) {
            if (GetAsyncKeyState(VK_UP) & 0x8000) {
                moveHelicopter('U');
            }
            if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                moveHelicopter('D');
            }
            if (GetAsyncKeyState('X') & 0x8000) {
                GameState::setGameRunning(false);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void InputThread::moveHelicopter(char direction) {
    std::lock_guard<std::mutex> lock(missileMutex);

    int currentY = helicopter.getY();

    switch (direction) {
    case 'U':
        if (currentY > 0) {
            helicopter.setY(currentY - HELICOPTER_SPEED);
        }
        break;
    case 'D':
        if (currentY < SCREEN_HEIGHT - 8) {
            helicopter.setY(currentY + HELICOPTER_SPEED);
        }
        break;
    }
}


