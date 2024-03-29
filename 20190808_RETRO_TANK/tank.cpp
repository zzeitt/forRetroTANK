#include "tank.h"

/******** Biu ********/
Biu::Biu(char ch_dir, unsigned short c, unsigned short r, EnumSpeed v,
         BiuType t) {
  first_mark = true;
  b_hit_tank = false;
  b_alife = true;
  cur_dir = ch_dir;
  cur_col = c;
  cur_row = r;
  speed = v;
  type = t;
}

bool Biu::hitTank() { return b_hit_tank; }

void Biu::printChar(unsigned short col, unsigned short row, string str) {
  gotoxy(2 * col + MARGIN_LEFT, row + MARGIN_UP);
  cout << str;
}

void Biu::printBlock(unsigned short col, unsigned short row) {
  printChar(col, row, "��");
}

void Biu::printBlank(unsigned short col, unsigned short row) {
  MAP[row][col] = BLANK;  // Everywhere bullet has passed will be set BLANK.
  printChar(col, row, "  ");
}

void Biu::printBiu() {
  if (cur_col >= 1 && cur_col <= COLS && cur_row >= 1 && cur_row <= ROWS) {
    MAP[cur_row][cur_col] = BIU;  // set position as MapElement TANK
    switch (cur_dir) {
      case 'w':
        printChar(cur_col, cur_row, type.ws_biu);
        break;
      case 's':
        printChar(cur_col, cur_row, type.ws_biu);
        break;
      case 'a':
        printChar(cur_col, cur_row, type.a_biu);
        break;
      case 'd':
        printChar(cur_col, cur_row, type.d_biu);
        break;
    }
  }
}

void Biu::eraseBiu() {
  if (cur_col >= 1 && cur_col <= COLS && cur_row >= 1 && cur_row <= ROWS) {
    printBlank(cur_col, cur_row);
  }
}

bool Biu::checkStaying() {
  if (cur_col >= 1 && cur_col <= COLS && cur_row >= 1 && cur_row <= ROWS) {
    if (C != FRAME) {
      if (C == BLANK || C == BIU) {
        return true;
      }
    }
  }
  return false;
}

void Biu::handleHit() {
  switch (C) {
    case BLOCK:
      C++;
      printBlank(cur_col, cur_row);
      break;
    case WALL:
      C++;
      printBlock(cur_col, cur_row);
      break;
    case TANK:
      b_hit_tank = true;
      break;
    default:
      break;
  }
  b_alife = false;
}

void Biu::autoFly() {
  if (checkStaying()) {
    // If can stay at current position.
    printBiu();
    time_this = high_resolution_clock::now();
    if (first_mark) {
      time_last = time_this;
      first_mark = false;
    } else {
      int duration =
          (int)duration_cast<milliseconds>(time_this - time_last).count();
      if (duration >= (MAX_SPEED - speed)) {
        // After gap time.
        eraseBiu();
        time_last = time_this;
        switch (cur_dir) {
          case 'w':
            cur_row--;
            break;
          case 's':
            cur_row++;
            break;
          case 'a':
            cur_col--;
            break;
          case 'd':
            cur_col++;
            break;
          default:
            break;
        }
      }
    }
  } else {
    // If can't stay at current position.
    handleHit();
  }
}

bool Biu::isAlife() { return b_alife; }

/******** Tank ********/
Tank::Tank(bool rob, char ch_dir, unsigned short c, unsigned short r,
           EnumSpeed v, GunType gun, unsigned short bm, EnumSpeed bs,
           BiuType bt) {
  b_robort = rob;
  first_mark = true;
  cur_dir = ch_dir;
  cur_col = c;
  cur_row = r;
  speed = v;
  gun_type = gun;
  biu_max = bm;
  biu_speed = bs;
  biu_type = bt;
  printTank();
}

void Tank::printChar(unsigned short col, unsigned short row, string str) {
  gotoxy(2 * col + MARGIN_LEFT, row + MARGIN_UP);
  cout << str;
}

void Tank::printBlock(unsigned short col, unsigned short row) {
  printChar(col, row, "��");
}

void Tank::printBlank(unsigned short col, unsigned short row) {
  MAP[row][col] = BLANK;  // Everywhere tank has passed will be set BLANK.
  printChar(col, row, "  ");
}

void Tank::printWheelsVer(unsigned short col, unsigned short row) {
  printChar(col - 1, row, "��");
  printChar(col + 1, row, "��");
}

void Tank::printWheelsHor(unsigned short col, unsigned short row) {
  printChar(col, row - 1, "��");
  printChar(col, row + 1, "��");
}

void Tank::printGunVer(unsigned short col, unsigned short row) {
  printChar(col, row, gun_type.ws_gun);
}

void Tank::printGunHor(unsigned short col, unsigned short row) {
  printChar(col, row, gun_type.ad_gun);
}

void Tank::printTank() {
  printBlock(cur_col, cur_row);  // Body of TANK.
  MAP[cur_row][cur_col] = TANK;  // set position as MapElement TANK
  switch (cur_dir) {
    case 'w':
    case 's':
      printWheelsVer(cur_col, cur_row);
      switch (cur_dir) {
        case 'w':
          printGunVer(cur_col, cur_row - 1);
          setBiuSource(cur_col, cur_row - 2);  // set bullet source position
          break;
        case 's':
          printGunVer(cur_col, cur_row + 1);
          setBiuSource(cur_col, cur_row + 2);
          break;
      }
      break;
    case 'a':
    case 'd':
      printWheelsHor(cur_col, cur_row);
      switch (cur_dir) {
        case 'a':
          printGunHor(cur_col - 1, cur_row);
          setBiuSource(cur_col - 2, cur_row);
          break;
        case 'd':
          printGunHor(cur_col + 1, cur_row);
          setBiuSource(cur_col + 2, cur_row);
          break;
      }
      break;
    default:
      setBiuSource(MARGIN_LEFT, MARGIN_BASELINE);
      break;
  }
}

void Tank::eraseTank() {
  printBlank(cur_col, cur_row);
  switch (cur_dir) {
    case 'w':
    case 's':
      printBlank(cur_col - 1, cur_row);
      printBlank(cur_col + 1, cur_row);
      switch (cur_dir) {
        case 'w':
          printBlank(cur_col, cur_row - 1);
          break;
        case 's':
          printBlank(cur_col, cur_row + 1);
          break;
      }
      break;
    case 'a':
    case 'd':
      printBlank(cur_col, cur_row - 1);
      printBlank(cur_col, cur_row + 1);
      switch (cur_dir) {
        case 'a':
          printBlank(cur_col - 1, cur_row);
          break;
        case 'd':
          printBlank(cur_col + 1, cur_row);
          break;
      }
      break;
  }
}

bool Tank::checkTurning(char dst_dir) {
  if (cur_dir == 'w' && dst_dir == 's') {
    return S == BLANK;
  }
  if (cur_dir == 's' && dst_dir == 'w') {
    return N == BLANK;
  }
  if (cur_dir == 'a' && dst_dir == 'd') {
    return E == BLANK;
  }
  if (cur_dir == 'd' && dst_dir == 'a') {
    return W == BLANK;
  }
  bool b_cur, b_dst;
  switch (cur_dir) {
    case 'w':
      b_cur = (WN == BLANK) * (N == BLANK) * (NE == BLANK) * (W == BLANK) *
              (C == BLANK || C == TANK) * (E == BLANK);
      break;
    case 'a':
      b_cur = (WN == BLANK) * (N == BLANK) * (W == BLANK) *
              (C == BLANK || C == TANK) * (SW == BLANK) * (S == BLANK);
      break;
    case 's':
      b_cur = (W == BLANK) * (C == BLANK || C == TANK) * (E == BLANK) *
              (SW == BLANK) * (S == BLANK) * (ES == BLANK);
      break;
    case 'd':
      b_cur = (N == BLANK) * (NE == BLANK) * (C == BLANK || C == TANK) *
              (E == BLANK) * (S == BLANK) * (ES == BLANK);
      break;
  }
  switch (dst_dir) {
    case 'w':
      b_dst = (WN == BLANK) * (N == BLANK) * (NE == BLANK) * (W == BLANK) *
              (C == BLANK || C == TANK) * (E == BLANK);
      break;
    case 'a':
      b_dst = (WN == BLANK) * (N == BLANK) * (W == BLANK) *
              (C == BLANK || C == TANK) * (SW == BLANK) * (S == BLANK);
      break;
    case 's':
      b_dst = (W == BLANK) * (C == BLANK || C == TANK) * (E == BLANK) *
              (SW == BLANK) * (S == BLANK) * (ES == BLANK);
      break;
    case 'd':
      b_dst = (N == BLANK) * (NE == BLANK) * (C == BLANK || C == TANK) *
              (E == BLANK) * (S == BLANK) * (ES == BLANK);
      break;
  }
  return b_cur * b_dst;
}

bool Tank::checkGoing() {
  bool b_forward;
  switch (cur_dir) {
    case 'w':
      b_forward =
          (WN == BLANK) * (NE == BLANK) * (MAP[cur_row - 2][cur_col] == BLANK);
      b_forward &= ((cur_row - 1) >= 1);
      break;
    case 'a':
      b_forward =
          (WN == BLANK) * (SW == BLANK) * (MAP[cur_row][cur_col - 2] == BLANK);
      b_forward &= ((cur_col - 1) >= 1);
      break;
    case 's':
      b_forward =
          (SW == BLANK) * (ES == BLANK) * (MAP[cur_row + 2][cur_col] == BLANK);
      b_forward &= ((cur_row + 1) <= ROWS);
      break;
    case 'd':
      b_forward =
          (NE == BLANK) * (ES == BLANK) * (MAP[cur_row][cur_col + 2] == BLANK);
      b_forward &= ((cur_col + 1) <= COLS);
      break;
    default:
      b_forward = false;
  }
  return b_forward;
}

void Tank::setBiuSource(unsigned short col, unsigned short row) {
  biu_source_col = col;
  biu_source_row = row;
}

void Tank::move(char dst_dir) {
  double duration;
  if (first_mark) {  // If this is the first move.
    time_this = high_resolution_clock::now();
    duration = MAX_SPEED;
  } else {
    time_this = high_resolution_clock::now();
    duration = (int)duration_cast<milliseconds>(time_this - time_last).count();
  }
  if (duration >= (MAX_SPEED - speed)) {
    if (dst_dir == cur_dir) {
      if (checkGoing()) {
        eraseTank();
        switch (cur_dir) {
          case 'w':
            cur_row--;
            break;
          case 's':
            cur_row++;
            break;
          case 'a':
            cur_col--;
            break;
          case 'd':
            cur_col++;
            break;
        }
        printTank();
        time_last = time_this;
        first_mark = false;
      }
    } else {
      if (dst_dir == 'w' || dst_dir == 'a' || dst_dir == 's' ||
          dst_dir == 'd') {
        if (checkTurning(dst_dir)) {
          eraseTank();
          cur_dir = dst_dir;
          printTank();
          time_last = time_this;
          first_mark = false;
        }
      }
    }
  }
}

void Tank::shoot() {
  if (v_biu.size() < biu_max) {
    Biu biu_temp(cur_dir, biu_source_col, biu_source_row, biu_speed, biu_type);
    v_biu.push_back(biu_temp);
  }
}

void Tank::checkBorders() {
  if (cur_col <= 1) {
    eraseTank();
    cur_col = 2;
    printTank();
  }
  if (cur_col >= COLS) {
    eraseTank();
    cur_col = COLS - 1;
    printTank();
  }
  if (cur_row <= 1) {
    eraseTank();
    cur_row = 2;
    printTank();
  }
  if (cur_row >= ROWS) {
    eraseTank();
    cur_row = ROWS - 1;
    printTank();
  }
}

bool Tank::isRobort() { return b_robort; }

char Tank::getDirection() { return cur_dir; }

unsigned short Tank::getColNum() { return cur_col; }

unsigned short Tank::getRowNum() { return cur_row; }

unsigned int Tank::getBiuLeft() { return biu_max - v_biu.size(); }
