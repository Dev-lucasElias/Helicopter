// collision_manager.h
#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "missile.h"
#include "dinosaur.h"
#include "helicopter.h"
#include "depot.h"
#include "truck.h"

class CollisionManager {
public:
    static bool checkMissileHit(const Missile& missile, const Dinosaur& dino);
    static bool checkHelicopterCollision(const Helicopter& heli, const Dinosaur& dino);
    static bool isOverDepot(const Helicopter& heli, const Depot& depot);
    static bool isTruckAtDepot(const Truck& truck, const Depot& depot);
};

#endif