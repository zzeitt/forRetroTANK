#pragma once
#include "game_frame.h"
#include "game_player.h"
#include <vector>

/***** Game Loop Class *****/
// Cope with the loop of game.
class GameLoop {
private:
  GameFrame g_frame;
  unsigned int col_row_num;
  std::vector<Player> v_player;
  std::vector<Tank> v_tank;
  bool checkWinning();
public:
  GameLoop();
  void initPlayers();
  void initTanks();
  void mainLoop();
};