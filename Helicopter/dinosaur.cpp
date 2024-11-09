// dinosaur.cpp (implementação)
#include "dinosaur.h"

Dinosaur::Dinosaur() : GameObject(), alive(false), headHeight(30) {}

bool Dinosaur::isAlive() const {
    return alive;
}

void Dinosaur::setAlive(bool state) {
    alive = state;
}

int Dinosaur::getHeadHeight() const {
    return headHeight;
}