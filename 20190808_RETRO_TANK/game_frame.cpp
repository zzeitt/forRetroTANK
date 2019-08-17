#include "game_frame.h"

void GameFrame::printChar(unsigned short col, unsigned short row, string str) {
  gotoxy(2 * col + MARGIN_LEFT, row + MARGIN_UP);
  cout << str;
}

void GameFrame::printBlock(unsigned short col, unsigned short row) {
  printChar(col, row, "█");
}
void GameFrame::printBlank(unsigned short col, unsigned short row) {
  printChar(col, row, "  ");
}
void GameFrame::printWall(unsigned short col, unsigned short row) {
  printChar(col, row, "▓");
}
void GameFrame::printStar(unsigned short col, unsigned short row) {
  printChar(col, row, "★");
}
void GameFrame::printUnknown(unsigned short col, unsigned short row) {
  printChar(col, row, "？");
}

void GameFrame::printFrame() {
  gotoxy(MARGIN_LEFT, 0);
  cout << "                           你已成功进入坦克深渊，开战吧！";
  gotoxy(MARGIN_LEFT, 1);
  cout << "☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆";
  /*gotoxy(MARGIN_LEFT, 2);
  cout << "01  03  05  07  09  11  13  15  17  19  21  23  25  27  29  31  33  "
          "35  37  39  41  43  ";
  gotoxy(MARGIN_LEFT, 3);
  cout << "  02  04  06  08  10  12  14  16  18  20  22  24  26  28  30  32  "
          "34  36  38  40  42  44";*/
}

unsigned int GameFrame::printMap() {
  gotoxy(MARGIN_LEFT, MARGIN_UP);
  // default tank HOUSE column is 3, default row is 11
  unsigned int col_temp = 3, row_temp = 11;
  for (int c = 0; c <= COLS + 1; c++) {
    for (int r = 0; r <= ROWS + 1; r++) {
      switch (MAP[r][c]) {
        case FRAME:
          printBlock(c, r);
          break;
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
        case HOUSE:
          col_temp = c;
          row_temp = r;
          printUnknown(c, r);
          break;
        default:
          printUnknown(c, r);
      }
    }
  }
  return col_temp * FACTOR_MID + row_temp;
}

void GameFrame::clearScreen() { system("cls"); }

void clearBase() {
  gotoxy(MARGIN_LEFT, MARGIN_BASELINE);
  cout << "                                                                    "
          "                ";
}

void outputBase(string s) {
  clearBase();
  gotoxy(MARGIN_LEFT, MARGIN_BASELINE);
  cout << s;
}

void outputBase(int i) {
  clearBase();
  gotoxy(MARGIN_LEFT, MARGIN_BASELINE);
  cout << i;
}
