#ifndef HELICOPTER_H
#define HELICOPTER_H

#include "depot.h"
#include <algorithm>

class Helicopter {
private:
    static const int MIN_MISSILES_WARNING = 3;
    static const int FIXED_X = 5;

    int y;
    int missileCount;
    std::mutex missileMutex;
    bool needReload;
    bool isReloading;
    bool alive;

public:
    Helicopter();

    // Getters
    int getX() const { return FIXED_X; }
    int getY() const { return y; }
    int getMissiles() const { return missileCount; }
    bool isAlive() const { return alive; }
    bool needsReload() const { return needReload; }
    bool getIsReloading() const { return isReloading; }

    // Setters
    void setY(int newY);
    void setMissiles(int count) { missileCount = count; }
    void setAlive(bool state) { missileCount = state; }
    void setNeedReload(bool state) { needReload = state; }
    void setIsReloading(bool state) { isReloading = state; }

    // Manipulação de mísseis
    void addMissiles(int count);
    void removeMissile();
    bool fireMissile(double targetX, double targetY);
    int getMissileCount() const;
    // Checagem de proximidade
    bool isNearDepot(const Depot& depot) const;
};

#endif