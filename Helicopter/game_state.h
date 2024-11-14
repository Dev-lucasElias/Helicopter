#define GAMESTATE_H
#ifndef GAMESTATE_H

#include <mutex>
using namespace std;


class GameState {
private:
    static bool gameRunning;
    static int score;
    static mutex mtx;

public:
    static bool isGameRunning() {
        lock_guard<mutex> lock(mtx);
        return gameRunning;
    }

    static void setGameRunning(bool state) {
        lock_guard<mutex> lock(mtx);
        gameRunning = state;
    }

    static int getScore() {
        lock_guard<mutex> lock(mtx);
        return score;
    }

    static void addScore(int points) {
        lock_guard<mutex> lock(mtx);
        score += points;
    }
};
#endif