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
            if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
                shootMissile();
            }
            if (GetAsyncKeyState('X') & 0x8000) {
                GameState::setGameRunning(false);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void InputThread::moveHelicopter(char direction) {
    std::lock_guard<std::mutex> lock(missileMutex);

    int currentY = helicopter.getY();

    switch (direction) {
    case 'U':
        if (currentY > 0) {
            RenderManager::eraseHelicopter(helicopter.getX(), currentY);
            helicopter.setY(currentY - HELICOPTER_SPEED);
        }
        break;
    case 'D':
        if (currentY < SCREEN_HEIGHT - 8) {
            RenderManager::eraseHelicopter(helicopter.getX(), currentY);
            helicopter.setY(currentY + HELICOPTER_SPEED);
        }
        break;
    }
}

void InputThread::shootMissile() {
    std::lock_guard<std::mutex> lock(missileMutex);
    if (helicopter.getMissiles() > 0) {
        for (auto& missile : missiles) {
            if (!missile.isActive()) {
                missile.setX(helicopter.getX() + 5);  // Sempre atira para a direita
                missile.setY(helicopter.getY());
                missile.setActive(true);
                missile.setDirection('R');  // Sempre atira para a direita
                helicopter.removeMissile();
                break;
            }
        }
    }
}
