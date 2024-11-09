
#include "helicopter_thread.h"
#include "game.h"
#include <iostream>
#include "helicopter.h"

HelicopterThread::HelicopterThread(Helicopter& h, Depot& d, std::vector<Missile>& m, std::mutex& mm)
    : helicopter(h), depot(d), missiles(m), missileMutex(mm) {}

void HelicopterThread::operator() {
    while (GameState::isGameRunning()) {
        if (helicopter.needsReload() &&
            CollisionManager::isOverDepot(helicopter, depot) &&
            !helicopter.getIsReloading()) {
            reloadHelicopter();
        }
        ConsoleManeger::delay(50);
    }
}

void HelicopterThread::reloadHelicopter() {
    std::unique_lock<std::mutex> depotLock(depot.getMutex());

    std::cout << "Helicóptero iniciando recarga...\n";

    while (depot.isTruckDocked()) {
        std::cout << "Aguardando caminhão finalizar...\n";
        depot.getSlotsAvailable().wait(depotLock);
    }

    depot.setHelicopterDocked(true);
    Helicopter.setIsReloading(true);

    int missilesNeeded = 10 - helicopter.getMissiles();
    int available = depot.countFilledSlots();
    int toLoad = std::min(missilesNeeded, available);

    if (toLoad > 0) {
        std::cout << "Recarregando " << toLoad << " mísseis...\n";

        for (int i = 0; i < 10 && toLoad > 0; i++) {
            if (depot.getSlot(i)) {
                depot.setSlot(i, false);
                helicopter.addMissiles(1);
                toLoad--;
                ConsoleManager::delay(100);
            }
        }

        std::cout << "Recarga completa! Mísseis: " << helicopter.getMissiles() << "\n";
    }
    else {
        std::cout << "Depósito vazio! Aguardando reabastecimento...\n";
    }

    helicopter.setNeedReload(helicopter.getMissiles() < MIN_MISSILES_WARNING);
    helicopter.setIsReloading(false);
    depot.setHelicopterDocked(false);

    depot.getRechargeComplete().notify_one();
}