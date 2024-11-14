// render_thread.h
#ifndef RENDER_THREAD_H
#define RENDER_THREAD_H

#include <vector>
#include <mutex>
#include "helicopter.h"
#include "missile.h"
#include "dinosaur.h"
#include "truck.h"
#include "depot.h"
#include "render_manager.h"
#include "game_state.h"
#include "console_maneger.h"

class RenderThread {
private:
    Helicopter& helicopter;
    std::vector<Missile>& missiles;
    std::vector<Dinosaur>& dinosaurs;
    Truck& truck;
    Depot& depot;
    std::mutex& missileMutex;
    std::mutex& dinoMutex;

public:
    RenderThread(Helicopter& h, std::vector<Missile>& m, std::vector<Dinosaur>& d,
        Truck& t, Depot& dp, std::mutex& mm, std::mutex& dm);
    void operator()();
};

#endif