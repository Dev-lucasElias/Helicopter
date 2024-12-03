#include "helicopter.h"
#include "game.h"
#include <algorithm>
#include <cstdlib> // para abs()

Helicopter::Helicopter()
    : y(SCREEN_HEIGHT / 2),
    missileCount(10),
    isReloading(false),
    alive(true),
    needReload(false) {}

void Helicopter::setY(int newY) {
    // Limita a posição Y entre 0 e SCREEN_HEIGHT - 20
    if (newY < 0) {
        y = 0;
    }
    else if (newY > SCREEN_HEIGHT - 8) {
        y = SCREEN_HEIGHT - 8;
    }
    else {
        y = newY;
    }
}

void Helicopter::addMissiles(int count) {
    std::lock_guard<std::mutex> lock(missileMutex);
    missileCount += count;
    if (missileCount >= MIN_MISSILES_WARNING) {
        needReload = false;
    }
}

void Helicopter::removeMissile() {
    if (missileCount > 0) {
        missileCount--;
        if (missileCount < MIN_MISSILES_WARNING) {
            needReload = true;
        }
    }
}

bool Helicopter::isNearDepot(const Depot& depot) const {
    // Como agora o X é fixo, só precisamos verificar se o depósito 
    // está próximo no eixo Y
    return abs(FIXED_X - depot.getX()) < DEPOT_WIDTH / 2 &&
        abs(y - depot.getY()) < DEPOT_HEIGHT / 2;
}

bool Helicopter::fireMissile(double targetX, double targetY) {
    std::lock_guard<std::mutex> lock(missileMutex);

    if (missileCount <= 0) {
        return false;  // Sem mísseis disponíveis
    }

    // Decrementa contador de mísseis
    missileCount--;

    // Aqui você pode criar e adicionar o míssil ao seu sistema de gerenciamento de entidades
    // Por exemplo:
    // gameWorld->addEntity(new Missile(position, targetX, targetY, 10.0));

    return true;
}

int Helicopter::getMissileCount() const {
    return missileCount;  // Leitura atômica, não precisa de mutex
}