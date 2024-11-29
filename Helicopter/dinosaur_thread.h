// dinosaur_thread.h
#ifndef DINOSAUR_THREAD_H
#define DINOSAUR_THREAD_H

#include "dinosaur.h"
#include "game_state.h"
#include <mutex>

class DinosaurThread {
private:
    Dinosaur& dinosaur;
    std::mutex& dinoMutex;
    int movementDuration;  // Duração do movimento atual
    int movementInterval; // Intervalo para mudar de direção

    void moveHorizontal();
    void jump();

public:
    DinosaurThread(Dinosaur& d, std::mutex& m);
    void operator()();
};

#endif