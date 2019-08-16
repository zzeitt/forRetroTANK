#pragma once
#include "game_frame.h"
#include "tank.h"
#include <vector>

/***** Game Loop Class *****/
// Cope with the loop of game.
class GameLoop {
private:
  // Fundamental frame of the whole game.
  GameFrame g_frame;
  // Attributes of Tank.
  int tank_dir;
  int tank_col;
  int tank_row;
  EnumSpeed tank_speed;
  GunType tank_gun;
  // Attribute of Bullets.
  unsigned int biu_max;
  EnumSpeed biu_speed;
  BiuType biu_type;

public:
  GameLoop();
  void setTankSpeed(EnumSpeed v);
  void setBiuSpeed(EnumSpeed v);
  void mainLoop();
};