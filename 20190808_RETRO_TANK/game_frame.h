#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include "map.h"

using namespace std;

/***** Inline Function ******/
// Fundamental function that allows cursors to
// move to specific location.
inline void gotoxy(unsigned short x, unsigned short y) {
  HANDLE hOut(GetStdHandle(STD_OUTPUT_HANDLE));
  COORD pos;
  pos.X = x;
  pos.Y = y;
  SetConsoleCursorPosition(hOut, pos);
  return;
}//需要头文件<Windows.h>，抄的，看不懂。。。

/***** Game Framework *****/
// Porvide methods for printing basic elements
// like 'Block' and 'Blank', etc.
class GameFrame {
private:
  void printChar(double col, double row, string str);
  void printBlock(double col, double row);
  void printBlank(double col, double row);
  void printWall(double col, double row);
  void printStar(double col, double row);
  void printUnkown(double col, double row);
public:
  void printFrame();
  void printMap();
  void clearScreen();
};

