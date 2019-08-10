#include "game_frame.h"

void GameFrame::printChar(double col, double row, string str) {
  gotoxy(2 * col, row + MARGIN_UP);
  cout << str;
}

void GameFrame::printBlock(double col, double row) { printChar(col, row, "█"); }
void GameFrame::printBlank(double col, double row) {
  printChar(col, row, "  ");
}
void GameFrame::printWall(double col, double row) { printChar(col, row, "▓"); }
void GameFrame::printStar(double col, double row) { printChar(col, row, "★"); }
void GameFrame::printUnkown(double col, double row) {
  printChar(col, row, "？");
}

void GameFrame::printFrame() {
  gotoxy(0, 0);
  cout << "                           你已成功进入坦克深渊，开战吧！！         "
          "            "
       << endl;
  cout << "☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆" << endl;
  cout << endl;
  gotoxy(0, MARGIN_UP);
  for (int c = 0; c <= COLS + 1; c++) {
    printBlock(c, 0);
  }
  for (int i = 1; i <= ROWS + 1; i++) {
    printBlock(0, i);
    printBlock(COLS + 1, i);
  }
  for (int c = 0; c <= COLS + 1; c++) {
    printBlock(c, ROWS + 1);
  }
}

void GameFrame::printMap() {
  for (int c = 1; c <= COLS; c++) {
    for (int r = 1; r <= ROWS; r++) {
      switch (MAP[r][c]) {
        case BLANK:
          printBlank(c, r);
          break;
        case BLOCK:
          printBlock(c, r);
          break;
        case WALL:
          printWall(c, r);
          break;
        case STAR:
          printStar(c, r);
          break;
        default:
          printUnkown(c, r);
      }
    }
  }
}

void GameFrame::clearScreen() { system("cls"); }
