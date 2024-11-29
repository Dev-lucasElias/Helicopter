// input_thread.cpp
#include "input_thread.h"

InputThread::InputThread(Helicopter& h, std::vector<Missile>& m, std::mutex& mm)
    : helicopter(h), missiles(m), missileMutex(mm) {}

void InputThread::operator()() {
    while (GameState::isGameRunning()) {
        if (!helicopter.getIsReloading()) {
            if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
                moveHelicopter('L');
            }
            if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
                moveHelicopter('R');
            }
            if (GetAsyncKeyState(VK_UP) & 0x8000) {
                moveHelicopter('U');
            }
            if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                moveHelicopter('D');
            }
            if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
                shootMissile();
            }
            if (GetAsyncKeyState('X') & 0x8000) {
                GameState::setGameRunning(false);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void InputThread::moveHelicopter(char direction) {
    std::lock_guard<std::mutex> lock(missileMutex);

    switch (direction) {
    case 'L':
        if (helicopter.getX() > 0) {
            helicopter.setX(helicopter.getX() - HELICOPTER_SPEED);
            helicopter.setDirection('L');
        }
        break;
    case 'R':
        if (helicopter.getX() < SCREEN_WIDTH - 20) {
            helicopter.setX(helicopter.getX() + HELICOPTER_SPEED);
            helicopter.setDirection('R');
        }
        break;
    case 'U':
        if (helicopter.getY() > 0) {
            helicopter.setY(helicopter.getY() - HELICOPTER_SPEED);
        }
        break;
    case 'D':
        if (helicopter.getY() < SCREEN_HEIGHT - 20) {
            helicopter.setY(helicopter.getY() + HELICOPTER_SPEED);
        }
        break;
    }
}

void InputThread::shootMissile() {
    std::lock_guard<std::mutex> lock(missileMutex);

    if (helicopter.getMissiles() > 0) {
        for (auto& missile : missiles) {
            if (!missile.isActive()) {
                missile.setX(helicopter.getX() + (helicopter.getDirection() == 'R' ? 5 : -1));
                missile.setY(helicopter.getY());
                missile.setActive(true);
                missile.setDirection(helicopter.getDirection());
                helicopter.removeMissile();
                break;
            }
        }
    }
}