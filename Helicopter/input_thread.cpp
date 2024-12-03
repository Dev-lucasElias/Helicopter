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
    // Precisamos proteger tanto o acesso aos m�sseis quanto ao helic�ptero
    std::lock_guard<std::mutex> missileLock(missileMutex);
    std::lock_guard<std::mutex> helicopterLock(helicopterMutex);

    // Verifica se o helic�ptero tem m�sseis dispon�veis
    if (helicopter.getMissileCount() <= 0) {
        return;  // N�o h� m�sseis dispon�veis para disparar
    }

    // Obt�m a posi��o atual do helic�ptero
    int helicopterX = helicopter.getX();
    int helicopterY = helicopter.getY();

    // Cria um novo m�ssil na posi��o do helic�ptero
    // O m�ssil se mover� da esquerda para a direita
    Missile newMissile(
        Position{ static_cast<double>(helicopterX + HELICOPTER_WIDTH), // Posi��o inicial X (frente do helic�ptero)
                static_cast<double>(helicopterY + HELICOPTER_HEIGHT / 2) }, // Posi��o inicial Y (centro do helic�ptero)
        static_cast<double>(SCREEN_WIDTH - helicopterX ), // Alvo X (fim da tela)
        static_cast<double>( helicopterY ), // Alvo Y (mesma altura do disparo)
        MISSILE_SPEED // Velocidade constante do m�ssil
    );

    // Adiciona o m�ssil ao vetor de m�sseis
    missiles.push_back(newMissile);

    // Decrementa o contador de m�sseis do helic�ptero
    helicopter.removeMissile();
}




