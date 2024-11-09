// depot.h
#ifndef DEPOT_H
#define DEPOT_H

#include <vector>
#include <mutex>
#include <condition_variable>
#include "game.h"

class Depot {
private:
    int x, y;
    std::vector<bool> slots;
    bool helicopterDocked;
    bool truckDocked;
    std::mutex mtx;
    std::condition_variable slotsAvailable;
    std::condition_variable rechargeComplete;

public:
    Depot();

    int getX() const;
    int getY() const;
    bool isHelicopterDocked() const;
    bool isTruckDocked() const;

    void setHelicopterDocked(bool state);
    void setTruckDocked(bool state);

    int countEmptySlots() const;
    int countFilledSlots() const;

    std::mutex& getMutex();
    std::condition_variable& getSlotsAvailable();
    std::condition_variable& getRechargeComplete();

    bool getSlot(int index) const;
    void setSlot(int index, bool state);
};

#endif