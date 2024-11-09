// missile.cpp
#include "missile.h"

Missile::Missile() : GameObject(), active(false) {}

bool Missile::isActive() const {
    return active;
}

void Missile::setActive(bool state) {
    active = state;
}