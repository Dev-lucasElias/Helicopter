// game_state.cpp
#include "game_state.h"

// Defini��o das vari�veis est�ticas
bool GameState::gameRunning = true;
int GameState::score = 0;
std::mutex GameState::mtx;