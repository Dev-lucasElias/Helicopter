// depot.cpp
#include "depot.h"
#include <algorithm>

Depot::Depot()
    : x(SCREEN_WIDTH - 100), y(SCREEN_HEIGHT - 50),
    slots(10, true), helicopterDocked(false), truckDocked(false) {}

int Depot::getX() const { return x; }
int Depot::getY() const { return y; }
bool Depot::isHelicopterDocked() const { return helicopterDocked; }
bool Depot::isTruckDocked() const { return truckDocked; }

void Depot::setHelicopterDocked(bool state) { helicopterDocked = state; }
void Depot::setTruckDocked(bool state) { truckDocked = state; }

int Depot::countEmptySlots() const {
    return std::count(slots.begin(), slots.end(), false);
}

int Depot::countFilledSlots() const {
    return std::count(slots.begin(), slots.end(), true);
}

std::mutex& Depot::getMutex() { return mtx; }
std::condition_variable& Depot::getSlotsAvailable() { return slotsAvailable; }
std::condition_variable& Depot::getRechargeComplete() { return rechargeComplete; }

bool Depot::getSlot(int index) const { return slots[index]; }
void Depot::setSlot(int index, bool state) { slots[index] = state; }