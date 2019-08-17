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
  gotoxy(MARGIN_LEFT, MARGIN_UP);
  for (int c = 0; c <= COLS + 1; c++) {
    printBlock(c, 0);         // upper border
    printBlock(c, ROWS + 1);  // lower border
  }
  for (int i = 1; i <= ROWS + 1; i++) {
    printBlock(0, i);         // left border
    printBlock(COLS + 1, i);  // right border
  }
}

unsigned int GameFrame::printMap() {
  // default column is 3, default row is 11
  unsigned int col_temp = 3, row_temp = 11;
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
