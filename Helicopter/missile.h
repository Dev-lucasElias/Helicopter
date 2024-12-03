// Missile.h
#ifndef MISSILE_H
#define MISSILE_H

#include <mutex>

struct Position {
    double x;
    double y;
};

class Missile {
private:
    Position position;
    double velocityX;
    double velocityY;
    bool active;
    double speed;

public:
    
    Missile(Position startPos, double targetX, double targetY, double missileSpeed);
    void update();
    bool isActive() const { return active; }
    Position getPosition() const { return position; }
    void deactivate() { active = false; }
    Missile();

};

#endif