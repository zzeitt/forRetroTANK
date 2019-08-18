#pragma once
#include <vector>
#include "game_frame.h"
#include "game_player.h"

/***** Game Loop Class *****/
// Cope with the loop of game.
class GameLoop {
 private:
  GameFrame g_frame;
  unsigned int col_row_num;  // initial col,row index of tank
  std::vector<Player> v_player;
  std::vector<Tank> v_tank;
  bool checkWinning();

 public:
  GameLoop();
  void initPlayers();
  void initTanks();
  void mainLoop();
};