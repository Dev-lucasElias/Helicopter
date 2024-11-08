#ifndef GAME_H
#define GAME_H

// Includes necessários
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>
#include <string>
#include <windows.h>
#include <conio.h>

// Definições globais
constexpr int SCREEN_WIDTH = 156;
constexpr int SCREEN_HEIGHT = 40;
constexpr int MAX_MISSILES = 20;
constexpr int MAX_DINOSAURS = 10;
constexpr int HELICOPTER_SPEED = 5;
constexpr int DINO_SPEED = 3;
constexpr int TRUCK_SPEED = 2;
constexpr int DEPOT_WIDTH = 50;
constexpr int DEPOT_HEIGHT = 30;
constexpr int MISSILES_PER_SLOT = 1;
constexpr int TRUCK_CAPACITY = 5;
constexpr int MIN_MISSILES_WARNING = 3;

// Cores
constexpr int SKY_COLOR = 1;
constexpr int GRASS_COLOR = 2;
constexpr int DINO_COLOR = 3;

using namespace std;

#endif