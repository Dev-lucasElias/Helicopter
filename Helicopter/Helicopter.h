// helicopter.h
#ifndef HELICOPTER_H
#define HELICOPTER_H

#include "gameobject.h"

class Helicopter : public GameObject {
private:
    int missiles;
    bool alive;
    bool needReload;
    bool isReloading;

public:
    Helicopter();

    int getMissiles() const;
    bool isAlive() const;
    bool needsReload() const;
    bool getIsReloading() const;

    void setMissiles(int count);
    void setAlive(bool state);
    void setNeedReload(bool state);
    void setIsReloading(bool state);

    void addMissiles(int count);
    void removeMissile();
};

#endif