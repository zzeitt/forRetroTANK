#pragma once
#include <Windows.h>
#include <conio.h>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
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
  bool b_hit_tank;
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
  // Handle hitting event.
  void handleHit();

 public:
  Biu(char ch_dir, unsigned short c, unsigned short r, EnumSpeed v, BiuType t);
  bool hitTank();
  void autoFly();
  bool isAlife();
};

/***** Class of Tank *****/
class Tank {
 private:
  bool b_robort;
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
  // Set bullet source position
  void setBiuSource(unsigned short col, unsigned short row);

 public:
  unsigned short biu_max;
  EnumSpeed biu_speed;
  BiuType biu_type;
  unsigned short biu_source_col;
  unsigned short biu_source_row;
  std::vector<Biu> v_biu;

  Tank(bool rob, char ch_dir, unsigned short c, unsigned short r, EnumSpeed v,
       GunType gun, unsigned short bm, EnumSpeed bs, BiuType bt);
  void move(char dst_dir);
  void shoot();
  void checkBorders();
  bool isRobort();
};