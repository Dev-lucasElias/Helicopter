// game_state.cpp
#include "game_state.h"

// Definição das variáveis estáticas
bool GameState::gameRunning = true;
int GameState::score = 0;
std::mutex GameState::mtx;