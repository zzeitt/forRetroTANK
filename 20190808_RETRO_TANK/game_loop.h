#pragma once
#include "game_frame.h"
#include "tank.h"

/***** Game Loop Class *****/
// Cope with the loop of game.
class GameLoop {
private:
  GameFrame g_frame;
  Tank tk;
public:
  GameLoop();
};