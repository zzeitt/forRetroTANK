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

char Player::genCommand(char cur_dir, unsigned short cur_col,
                        unsigned short cur_row, int biu_left) {
  // Detect the whole MAP first
  unsigned short enemy_col = tank_col;
  unsigned short enemy_row = tank_row;
  for (int i = 0; i <= COLS + 1; i++) {
    for (int j = 0; j <= ROWS + 1; j++) {
      if (C == TANK) {
        enemy_col = i;
        enemy_row = j;
      }
    }
  }
  // Generate command
  int col_dis = enemy_col - cur_col;
  int row_dis = enemy_row - cur_row;
  // Random test
  srand(time(NULL));
  int i_rand = rand() % 6;
  switch (i_rand) {
    case 0:
      return 'w';
      break;
    case 1:
      return 'a';
      break;
    case 2:
      return 's';
      break;
    case 3:
      return 'd';
      break;
    case 4:
      return 'j';
      break;
    default:
      return '?';
      break;
  }
}
