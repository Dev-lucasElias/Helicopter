// helicopter.cpp
#include "helicopter.h"
#include "game.h"

Helicopter::Helicopter()
    : GameObject(), missiles(10), alive(true),
    needReload(false), isReloading(false) {}

int Helicopter::getMissiles() const { return missiles; }
bool Helicopter::isAlive() const { return alive; }
bool Helicopter::needsReload() const { return needReload; }
bool Helicopter::getIsReloading() const { return isReloading; }

void Helicopter::setMissiles(int count) { missiles = count; }
void Helicopter::setAlive(bool state) { alive = state; }
void Helicopter::setNeedReload(bool state) { needReload = state; }
void Helicopter::setIsReloading(bool state) { isReloading = state; }

void Helicopter::addMissiles(int count) { missiles += count; }
void Helicopter::removeMissile() {
    if (missiles > 0) missiles--;
    if (missiles < MIN_MISSILES_WARNING) needReload = true;
}