#include "game_player.h"

Player::Player() {
  b_robort = true;
  // Default settings for Tank.
  tank_dir = 'a';
  tank_col = 20;
  tank_row = 9;
  tank_speed = FAST;
  tank_gun = gun_a;
  // Default settings for Bullets.
  biu_max = 5;
  biu_speed = MEDIUM;
  biu_type = biu_a;
}

void Player::setAutoOperator(bool b) {
  if (!b) {
    b_robort = false;
  } else {
    b_robort = true;
  }
}

void Player::setTankDirection(char d) { tank_dir = d; }

void Player::setTankColNum(unsigned short c) { tank_col = c; }

void Player::setTankRowNum(unsigned short r) { tank_row = r; }

void Player::setTankSpeed(EnumSpeed v) { tank_speed = v; }

void Player::setTankGun(GunType g) { tank_gun = g; }

void Player::setBiuMaxNum(unsigned short m) { biu_max = m; }

void Player::setBiuSpeed(EnumSpeed v) { biu_speed = v; }

void Player::setBiuType(BiuType b) { biu_type = b; }
