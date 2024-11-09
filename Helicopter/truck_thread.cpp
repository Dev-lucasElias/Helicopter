// truck_thread.cpp
#include "truck_thread.h"
#include "game.h"
#include <iostream>

TruckThread::TruckThread(Truck& t, Depot& d) : truck(t), depot(d) {}

void TruckThread::operator()() {
    while (GameState::isGameRunning()) {
        if (!truck.getIsUnloading()) {
            moveTruck();
        }

        if (truck.getMissiles() > 0 && CollisionManager::isTruckAtDepot(truck, depot)) {
            unloadTruck();
        }

        if (truck.getMissiles() == 0) {
            reloadTruck();
        }

        ConsoleManager::delay(100);
    }
}

void TruckThread::moveTruck() {
    if (truck.getDirection() == 'R') {
        if (truck.getX() < SCREEN_WIDTH - 20) {
            truck.setX(truck.getX() + TRUCK_SPEED);
        }
        else {
            truck.setDirection('L');
        }
    }
    else {
        if (truck.getX() > 0) {
            truck.setX(truck.getX() - TRUCK_SPEED);
        }
        else {
            truck.setDirection('R');
        }
    }
}

void TruckThread::unloadTruck() {
    std::unique_lock<std::mutex> depotLock(depot.getMutex());

    while (depot.isHelicopterDocked()) {
        depot.getRechargeComplete().wait(depotLock);
    }

    depot.setTruckDocked(true);
    truck.setIsUnloading(true);

    int emptySlots = depot.countEmptySlots();
    int toUnload = std::min(truck.getMissiles(), emptySlots);

    if (toUnload > 0) {
        std::cout << "Descarregando " << toUnload << " mísseis...\n";

        for (int i = 0; i < 10 && toUnload > 0; i++) {
            if (!depot.getSlot(i)) {
                depot.setSlot(i, true);
                truck.removeMissile();
                toUnload--;
                ConsoleManager::delay(200);
            }
        }
    }

    truck.setIsUnloading(false);
    depot.setTruckDocked(false);
    depot.getSlotsAvailable().notify_one();
}

void TruckThread::reloadTruck() {
    truck.setX(0);
    std::cout << "Caminhão reabastecendo...\n";
    ConsoleManager::delay(3000);
    truck.reload();
    std::cout << "Caminhão reabastecido com " << truck.getMissiles() << " mísseis\n";
}