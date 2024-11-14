
#include "collision_manager.h"
#include "game.h"  // para DEPOT_WIDTH e DEPOT_HEIGHT
#include <cstdlib> // para abs()

bool CollisionManager::checkMissileHit(const Missile& missile, const Dinosaur& dino) {
    return (abs(missile.getX() - dino.getX()) < 10 &&
        abs(missile.getY() - (dino.getY() + dino.getHeadHeight())) < 5);
}

bool CollisionManager::checkHelicopterCollision(const Helicopter& heli, const Dinosaur& dino) {
    return (abs(heli.getX() - dino.getX()) < 15 &&
        abs(heli.getY() - dino.getY()) < 15);
}

bool CollisionManager::isOverDepot(const Helicopter& heli, const Depot& depot) {
    return (abs(heli.getX() - depot.getX()) < DEPOT_WIDTH / 2 &&
        abs(heli.getY() - depot.getY()) < DEPOT_HEIGHT / 2);
}

bool CollisionManager::isTruckAtDepot(const Truck& truck, const Depot& depot) {
    return abs(truck.getX() - depot.getX()) < DEPOT_WIDTH / 2;
}