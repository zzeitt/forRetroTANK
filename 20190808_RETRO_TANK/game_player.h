#pragma once
#include "game_frame.h"
#include "tank.h"

class Player {
 public:
  /****************** Variables ******************/
  bool b_robort;
  // Attributes of Tank.
  char tank_dir;
  unsigned short tank_col;
  unsigned short tank_row;
  EnumSpeed tank_speed;
  GunType tank_gun;
  // Attribute of Bullets.
  unsigned short biu_max;
  EnumSpeed biu_speed;
  BiuType biu_type;
  /****************** Functions ******************/
  Player();
  void setAutoOperator(bool b);
  void setTankDirection(char d);
  void setTankColNum(unsigned short c);
  void setTankRowNum(unsigned short r);
  void setTankSpeed(EnumSpeed v);
  void setTankGun(GunType g);
  void setBiuMaxNum(unsigned short m);
  void setBiuSpeed(EnumSpeed v);
  void setBiuType(BiuType b);
  /****************** Automation ******************/
  char genCommand(char cur_dir, unsigned short cur_col, unsigned short cur_row,
                  int biu_left);
};
