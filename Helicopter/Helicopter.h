#ifndef HELICOPTER_H
#define HELICOPTER_H

#include "depot.h"
#include <algorithm>

class Helicopter {
private:
    static const int MIN_MISSILES_WARNING = 3;
    static const int FIXED_X = 5;

    int y;
    int missiles;
    bool alive;
    bool needReload;
    bool isReloading;

public:
    Helicopter();

    // Getters
    int getX() const { return FIXED_X; }
    int getY() const { return y; }
    int getMissiles() const { return missiles; }
    bool isAlive() const { return alive; }
    bool needsReload() const { return needReload; }
    bool getIsReloading() const { return isReloading; }

    // Setters
    void setY(int newY);
    void setMissiles(int count) { missiles = count; }
    void setAlive(bool state) { alive = state; }
    void setNeedReload(bool state) { needReload = state; }
    void setIsReloading(bool state) { isReloading = state; }

    // Manipula��o de m�sseis
    void addMissiles(int count);
    void removeMissile();

    // Checagem de proximidade
    bool isNearDepot(const Depot& depot) const;
};

#endif