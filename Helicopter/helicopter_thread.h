// helicopter_thread.h
#ifndef HELICOPTER_THREAD_H
#define HELICOPTER_THREAD_H

#include "helicopter.h"
#include "depot.h"
#include "missile.h"
#include "game_state.h"
#include <mutex>
#include <vector>

class HelicopterThread {
private:
	Helicopter& helicopter;
	Depot& depot;
	std::vector<Missile>& missiles;
	std::mutex& missileMutex;

public:
	HelicopterThread(Helicopter& h, Depot& d, std::vector<Missile>& m, std::mutex& mm);
	void operator()();
};

#endif