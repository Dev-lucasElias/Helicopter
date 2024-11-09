// truck.h
#ifndef TRUCK_H
#define TRUCK_H

#include "gameobject.h"

class Truck : public GameObject {
private:
    int missiles;
    bool isMoving;
    bool isUnloading;

public:
    Truck();

    int getMissiles() const;
    bool getIsMoving() const;
    bool getIsUnloading() const;

    void setMissiles(int count);
    void setIsMoving(bool state);
    void setIsUnloading(bool state);

    void removeMissile();
    void reload();
};

#endif