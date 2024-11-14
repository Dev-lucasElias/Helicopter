// gameobject.cpp
#include "gameobject.h"

GameObject::GameObject(int x, int y, char direction)
    : x(x), y(y), direction(direction) {}

int GameObject::getX() const { return x; }
int GameObject::getY() const { return y; }
char GameObject::getDirection() const { return direction; }

void GameObject::setX(int newX) { x = newX; }
void GameObject::setY(int newY) { y = newY; }
void GameObject::setDirection(char newDir) { direction = newDir; }