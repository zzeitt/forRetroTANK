#pragma once

/***** Constant Variables of Map *****/
const unsigned int MARGIN_UP = 4;
const unsigned int MARGIN_BASELINE = 26;
const unsigned int MARGIN_LEFT = 16;
const unsigned int ROWS = 18, COLS = 42;
const unsigned int FACTOR_MID = 10000;  // factor_temp should ensure the division

extern int MAP[ROWS + 2][COLS + 2];

/***** Enumerated Map's Elements *****/
enum MapElement {
  TANK = -9,
  BIU = -8,
  STAR = -6,
  WALL = -1,
  BLOCK = 0,
  ////////////////////////
  BLANK = 1,
  HOUSE = 7,
  FRAME = 9,
};