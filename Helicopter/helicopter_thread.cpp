// helicopter_thread.cpp
#include "helicopter_thread.h"
#include <thread>

HelicopterThread::HelicopterThread(Helicopter& h, Depot& d, std::vector<Missile>& m, std::mutex& mm)
    : helicopter(h), depot(d), missiles(m), missileMutex(mm) {}

void HelicopterThread::operator()() {
    while (GameState::isGameRunning()) {
        {
            std::lock_guard<std::mutex> lock(missileMutex);

            // Verificar se está próximo ao depósito
            if (helicopter.needsReload() && helicopter.isNearDepot(depot)) {
                helicopter.setMissiles(MAX_MISSILES);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}