// helicopter.h
#ifndef HELICOPTER_H
#define HELICOPTER_H

#include "gameobject.h"
#include "depot.h"

class Helicopter : public GameObject {
private:
    int missiles;
    bool alive;
    bool needReload;
    bool isReloading;

public:
    // Construtor e métodos que já tem implementação
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
    bool isNearDepot(const Depot& depot) const;
};

#endif