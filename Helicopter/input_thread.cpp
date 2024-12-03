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
            if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
                shootMissile();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
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

void InputThread::shootMissile() {
    // Precisamos proteger tanto o acesso aos mísseis quanto ao helicóptero
    std::lock_guard<std::mutex> missileLock(missileMutex);
    std::lock_guard<std::mutex> helicopterLock(helicopterMutex);

    // Verifica se o helicóptero tem mísseis disponíveis
    if (helicopter.getMissileCount() <= 0) {
        return;  // Não há mísseis disponíveis para disparar
    }

    // Obtém a posição atual do helicóptero
    int helicopterX = helicopter.getX();
    int helicopterY = helicopter.getY();

    // Cria um novo míssil na posição do helicóptero
    // O míssil se moverá da esquerda para a direita
    Missile newMissile(
        Position{ static_cast<double>(helicopterX + HELICOPTER_WIDTH), // Posição inicial X (frente do helicóptero)
                static_cast<double>(helicopterY + HELICOPTER_HEIGHT / 2) }, // Posição inicial Y (centro do helicóptero)
        static_cast<double>(SCREEN_WIDTH - helicopterX ), // Alvo X (fim da tela)
        static_cast<double>( helicopterY ), // Alvo Y (mesma altura do disparo)
        MISSILE_SPEED // Velocidade constante do míssil
    );

    // Adiciona o míssil ao vetor de mísseis
    missiles.push_back(newMissile);

    // Decrementa o contador de mísseis do helicóptero
    helicopter.removeMissile();
}




