// truck.cpp
#include "truck.h"
#include "game.h"

Truck::Truck()
    : GameObject(), missiles(TRUCK_CAPACITY),
    isMoving(true), isUnloading(false) {}

int Truck::getMissiles() const { return missiles; }
bool Truck::getIsMoving() const { return isMoving; }
bool Truck::getIsUnloading() const { return isUnloading; }

void Truck::setMissiles(int count) { missiles = count; }
void Truck::setIsMoving(bool state) { isMoving = state; }
void Truck::setIsUnloading(bool state) { isUnloading = state; }

void Truck::removeMissile() { if (missiles > 0) missiles--; }
void Truck::reload() { missiles = TRUCK_CAPACITY; }