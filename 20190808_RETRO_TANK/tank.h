#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include "game_frame.h"

using namespace std;


#define N MAP[cur_row-1][cur_col]
#define NE MAP[cur_row-1][cur_col+1]
#define E MAP[cur_row][cur_col+1]
#define ES MAP[cur_row+1][cur_col+1]
#define S MAP[cur_row+1][cur_col]
#define SW MAP[cur_row+1][cur_col-1]
#define W MAP[cur_row][cur_col-1]
#define WN MAP[cur_row-1][cur_col-1]

/***** Enumerated Speed *****/
enum EnumSpeed {
  veryfast = 200,
  sofast = 180,
  fast = 150,
  medium = 100,
  slow = 0
};  //世界频道-速度

/***** Type of Gun *****/
struct GunType {
  char ws_gun[3];
  char ad_gun[3];
};
static GunType gun_a = {"||", "=="}, gun_b = {"‥", "："};

/***** Type of Bullet *****/
struct BiuType {
  char ws_biu[3];
  char a_biu[3];
  char d_biu[3];
};
static BiuType biu_a = {"oo", " 8", "8 "}, biu_b = {"‥", "：", "："};

/***** Class of Tank *****/
class Tank {
private:
  char cur_dir;
  int cur_col;
  int cur_row;
  EnumSpeed speed;
  GunType gun_type;
  BiuType biu_type;
  void printChar(double col, double row, string str);
  void printBlock(double col, double row);
  void printBlank(double col, double row);
  void printStar(double col, double row);
  void printBiu(double col, double row);

  void printTank();
  void eraseTank();
  void printWin();
public:
  Tank();
  Tank(char ch_dir, int c, int r, EnumSpeed v, GunType gun, BiuType biu);
  bool checkTurning(char dst_dir);
  bool checkGoing();
  bool checkWinning();
  void move(char dst_dir);
  void animateBiu(EnumSpeed biuspeed);
};