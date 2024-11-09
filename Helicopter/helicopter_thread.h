// helicopter_thread.h
#ifndef HELICOPTER_THREAD_H
#define HELICOPTER_THREAD_H

#include <vector>
#include <mutex>
#include "helicopter.h"
#include "depot.h"
#include "missile.h"
#include "collision_manager.h"
#include "game_state.h"
#include "console_maneger.h"

class HelicopterThread {
private:
   Helicopter& helicopter;
   Depot& depot;
   std::vector<Missile>& missiles;
   std::mutex& missileMutex;

   void reloadHelicopter();

public:
   HelicopterThread(Helicopter& h, Depot& d, std::vector<Missile>& m, std::mutex& mm);
   void operator()();
};

#endif