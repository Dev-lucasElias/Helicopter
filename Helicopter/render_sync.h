#include "Game_state.h"
#pragma once
#include <mutex>
#include "render_thread.h"

class RenderSync {
private:
    static std::mutex renderMutex;
    static bool isLocked;
public:
    static void beginRender() {
        if (!isLocked) {
            renderMutex.lock();
            isLocked = true;
        }
    }

    static void endRender() {
        if (isLocked) {
            renderMutex.unlock();
            isLocked = false;
        }
    }
};