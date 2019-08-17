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
  //const unsigned short BORDER_LEFT = MARGIN_LEFT;
  //const unsigned short BORDER_RIGHT = MARGIN_LEFT + 2*COLS + 1;
  //const unsigned short BORDER_UP = MARGIN_UP;
  //const unsigned short BORDER_DOWN = MARGIN_UP + ROWS + 1;
  void printChar(unsigned short col, unsigned short row, string str);
  void printBlock(unsigned short col, unsigned short row);
  void printBlank(unsigned short col, unsigned short row);
  void printWall(unsigned short col, unsigned short row);
  void printStar(unsigned short col, unsigned short row);
  void printUnknown(unsigned short col, unsigned short row);
public:
  void printFrame();
  unsigned int printMap();
  void clearScreen();
};

/***** Debug function *****/
void clearBase();
void outputBase(string s);
void outputBase(int i);
