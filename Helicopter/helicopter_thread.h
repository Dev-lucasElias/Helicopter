// helicopter_thread.h
#ifndef HELICOPTER_THREAD_H
#define HELICOPTER_THREAD_H

#include "game.h"
#include "helicopter.h"
#include "depot.h"
#include "missile.h"

class HelicopterThread {
private:
    Helicopter& helicopter;
    Depot& depot;
    vector<Missile>& missiles;
    mutex& missileMutex;

public:
    HelicopterThread(Helicopter& h, Depot& d, vector<Missile>& m, mutex& mm);
    void operator()();

private:
    void reloadHelicopter();
};

#endif