// truck_thread.h
#ifndef TRUCK_THREAD_H
#define TRUCK_THREAD_H

#include "truck.h"
#include "depot.h"
#include "game_state.h"
#include "collision_manager.h"
#include "console_maneger.h"

class TruckThread {
private:
	Truck& truck;
	Depot& depot;

	void moveTruck();
	void unloadTruck();
	void reloadTruck();

public:
	TruckThread(Truck& t, Depot& d);
	void operator()();
};

#endif