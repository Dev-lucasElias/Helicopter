// input_thread.h
#ifndef INPUT_THREAD_H
#define INPUT_THREAD_H

#include <vector>
#include <mutex>
#include <windows.h>
#include "helicopter.h"
#include "missile.h"
#include "game_state.h"
#include "console_maneger.h"
#include "game.h"
#include "render_manager.h"
#include "render_sync.h"

class InputThread {
private:
    Helicopter& helicopter;
    std::vector<Missile>& missiles;
    std::mutex& missileMutex;
    std::mutex& helicopterMutex;

    void moveHelicopter(char direction);
    void shootMissile();

public:
    InputThread(Helicopter& h, std::vector<Missile>& m, std::mutex& mm, std::mutex& hm);
    void operator()();
    
};

#endif