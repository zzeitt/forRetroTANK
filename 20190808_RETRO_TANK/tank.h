#pragma once
#include <Windows.h>
#include <conio.h>
#include <chrono>
#include <iostream>
#include <string>
#include "game_frame.h"

using namespace std;
using namespace std::chrono;

#define N MAP[cur_row - 1][cur_col]
#define NE MAP[cur_row - 1][cur_col + 1]
#define E MAP[cur_row][cur_col + 1]
#define ES MAP[cur_row + 1][cur_col + 1]
#define S MAP[cur_row + 1][cur_col]
#define SW MAP[cur_row + 1][cur_col - 1]
#define W MAP[cur_row][cur_col - 1]
#define WN MAP[cur_row - 1][cur_col - 1]
#define C MAP[cur_row][cur_col]

/***** Enumerated Speed *****/
const int MAX_SPEED = 200;
enum EnumSpeed {
  SO_FAST = 180,
  FAST = 150,
  MEDIUM = 100,
  SLOW = 0
};  //世界频道-速度

/***** Struct of Gun *****/
struct GunType {
  char ws_gun[3];
  char ad_gun[3];
};
static GunType gun_a = {"||", "=="}, gun_b = {"‥", "："};

/***** Struct of Bullet *****/
struct BiuType {
  char ws_biu[3];
  char a_biu[3];
  char d_biu[3];
};
static BiuType biu_a = {"oo", " 8", "8 "}, biu_b = {"‥", "：", "："};

/***** Class of Bullet *****/
class Biu {
 private:
  bool first_mark;
  bool b_alife;
  high_resolution_clock::time_point time_last;
  high_resolution_clock::time_point time_this;
  // Bullet attributes.
  char cur_dir;
  unsigned short cur_col;
  unsigned short cur_row;
  EnumSpeed speed;
  BiuType type;
  // Fundamental function for printing elements.
  void printChar(unsigned short col, unsigned short row, string str);
  // Low-level functions for printing.
  void printBlock(unsigned short col, unsigned short row);
  void printBlank(unsigned short col, unsigned short row);
  // Advanced functions for printing.
  void printBiu();
  void eraseBiu();
  // Checking function(s).
  bool checkStaying();

 public:
  Biu(char ch_dir, int c, int r);
  Biu(char ch_dir, int c, int r, EnumSpeed v, BiuType t);
  void autoFly();
  bool isAlife();
};

/***** Class of Tank *****/
class Tank {
 private:
  bool first_mark;
  high_resolution_clock::time_point time_last;
  high_resolution_clock::time_point time_this;
  // Tank attributes.
  char cur_dir;
  unsigned short cur_col;
  unsigned short cur_row;
  EnumSpeed speed;
  GunType gun_type;
  // Fundamental function for printing elements.
  void printChar(unsigned short col, unsigned short row, string str);
  // Low-level functions for printing parts of TANK.
  void printBlock(unsigned short col, unsigned short row);
  void printBlank(unsigned short col, unsigned short row);
  void printWheelsVer(unsigned short col, unsigned short row);
  void printWheelsHor(unsigned short col, unsigned short row);
  void printGunVer(unsigned short col, unsigned short row);
  void printGunHor(unsigned short col, unsigned short row);
  // Adavanced functions for printing.
  void printTank();
  void eraseTank();
  // Checking functions.
  bool checkTurning(char dst_dir);
  bool checkGoing();

 public:
  Tank();
  Tank(char ch_dir, int c, int r, EnumSpeed v, GunType gun);
  void move(char dst_dir);
  char getDirection();
  int getBiuColNum();
  int getBiuRowNum();
  void checkBorders();
  bool checkWinning();
};