#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "game.h"

class GameObject {
protected:
    int x, y;
    char direction;

public:
    GameObject(int x = 0, int y = 0, char direction = 'R');

    int getX() const;
    int getY() const;
    char getDirection() const;

    void setX(int newX);
    void setY(int newY);
    void setDirection(char newDir);
};

#endif