#include "tank.h"

/******** Biu ********/
Biu::Biu(char ch_dir, int c, int r) {
  first_mark = true;
  b_alife = true;
  cur_dir = ch_dir;
  cur_col = c;
  cur_row = r;
  speed = FAST;
  type = biu_a;
}

Biu::Biu(char ch_dir, int c, int r, EnumSpeed v, BiuType t) {
  first_mark = true;
  b_alife = true;
  cur_dir = ch_dir;
  cur_col = c;
  cur_row = r;
  speed = v;
  type = t;
}

void Biu::printChar(unsigned short col, unsigned short row, string str) {
  gotoxy(2 * col + MARGIN_LEFT, row + MARGIN_UP);
  cout << str;
}

void Biu::printBlock(unsigned short col, unsigned short row) {
  printChar(col, row, "¨€");
}

void Biu::printBlank(unsigned short col, unsigned short row) {
  printChar(col, row, "  ");
}

void Biu::printBiu() {
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

void Biu::eraseBiu() { printBlank(cur_col, cur_row); }

bool Biu::checkGoing() {
  if (MAP[cur_row][cur_col] == BLOCK || MAP[cur_row][cur_col] == WALL ||
      MAP[cur_row][cur_col] == STAR) {
    return false;
  } else {
    bool b_forward;
    switch (cur_dir) {
      case 'w':
        b_forward = (N == BLANK);
        break;
      case 'a':
        b_forward = (W == BLANK);
        break;
      case 's':
        b_forward = (S == BLANK);
        break;
      case 'd':
        b_forward = (E == BLANK);
        break;
      default:
        b_forward = false;
    }
    return b_forward;
  }
}

void Biu::move() {
  if (cur_col >= 1 && cur_col <= COLS && cur_row >= 1 && cur_row <= ROWS) {
    int duration;
    if (first_mark) {  // If this is the first move.
      time_this = high_resolution_clock::now();
      duration = MAX_SPEED;
    } else {
      time_this = high_resolution_clock::now();
      duration =
          (int)duration_cast<milliseconds>(time_this - time_last).count();
    }
    if (duration >= (MAX_SPEED - speed)) {
      if (checkGoing()) {  // If confront with BLANK.
        eraseBiu();
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
        printBiu();
        time_last = time_this;
        first_mark = false;
      } else {  // If confront with non-BLANK.
        // eraseBiu();
        // handleHit();
        b_alife = false;
      }
    }
  } else {
    b_alife = false;
  }
}

bool Biu::isAlife() { return b_alife; }

void Biu::handleDeath()
{
  if (!b_alife) {

  }
}

/******** Tank ********/
Tank::Tank() {
  first_mark = true;
  cur_dir = 'w';
  cur_col = 20;
  cur_row = 9;
  speed = FAST;
  gun_type = gun_a;
  printTank();
}

Tank::Tank(char ch_dir, int c, int r, EnumSpeed v, GunType gun) {
  first_mark = true;
  cur_dir = ch_dir;
  cur_col = c;
  cur_row = r;
  speed = v;
  gun_type = gun;
  printTank();
}

void Tank::printChar(unsigned short col, unsigned short row, string str) {
  gotoxy(2 * col + MARGIN_LEFT, row + MARGIN_UP);
  cout << str;
}

void Tank::printBlock(unsigned short col, unsigned short row) {
  printChar(col, row, "¨€");
}

void Tank::printBlank(unsigned short col, unsigned short row) {
  printChar(col, row, "  ");
}

void Tank::printWheelsVer(unsigned short col, unsigned short row) {
  printChar(col - 1, row, "©¯");
  printChar(col + 1, row, "©¯");
}

void Tank::printWheelsHor(unsigned short col, unsigned short row) {
  printChar(col, row - 1, "¡­");
  printChar(col, row + 1, "¡­");
}

void Tank::printGunVer(unsigned short col, unsigned short row) {
  printChar(col, row, gun_type.ws_gun);
}

void Tank::printGunHor(unsigned short col, unsigned short row) {
  printChar(col, row, gun_type.ad_gun);
}

void Tank::printTank() {
  printBlock(cur_col, cur_row);  // Body of TANK.
  switch (cur_dir) {
    case 'w':
    case 's':
      printWheelsVer(cur_col, cur_row);
      switch (cur_dir) {
        case 'w':
          printGunVer(cur_col, cur_row - 1);
          break;
        case 's':
          printGunVer(cur_col, cur_row + 1);
          break;
      }
      break;
    case 'a':
    case 'd':
      printWheelsHor(cur_col, cur_row);
      switch (cur_dir) {
        case 'a':
          printGunHor(cur_col - 1, cur_row);
          break;
        case 'd':
          printGunHor(cur_col + 1, cur_row);
          break;
      }
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
              (MAP[cur_row][cur_col] == BLANK) * (E == BLANK);
      break;
    case 'a':
      b_cur = (WN == BLANK) * (N == BLANK) * (W == BLANK) *
              (MAP[cur_row][cur_col] == BLANK) * (SW == BLANK) * (S == BLANK);
      break;
    case 's':
      b_cur = (W == BLANK) * (MAP[cur_row][cur_col] == BLANK) * (E == BLANK) *
              (SW == BLANK) * (S == BLANK) * (ES == BLANK);
      break;
    case 'd':
      b_cur = (N == BLANK) * (NE == BLANK) * (MAP[cur_row][cur_col] == BLANK) *
              (E == BLANK) * (S == BLANK) * (ES == BLANK);
      break;
  }
  switch (dst_dir) {
    case 'w':
      b_dst = (WN == BLANK) * (N == BLANK) * (NE == BLANK) * (W == BLANK) *
              (MAP[cur_row][cur_col] == BLANK) * (E == BLANK);
      break;
    case 'a':
      b_dst = (WN == BLANK) * (N == BLANK) * (W == BLANK) *
              (MAP[cur_row][cur_col] == BLANK) * (SW == BLANK) * (S == BLANK);
      break;
    case 's':
      b_dst = (W == BLANK) * (MAP[cur_row][cur_col] == BLANK) * (E == BLANK) *
              (SW == BLANK) * (S == BLANK) * (ES == BLANK);
      break;
    case 'd':
      b_dst = (N == BLANK) * (NE == BLANK) * (MAP[cur_row][cur_col] == BLANK) *
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
      break;
    case 'a':
      b_forward =
          (WN == BLANK) * (SW == BLANK) * (MAP[cur_row][cur_col - 2] == BLANK);
      break;
    case 's':
      b_forward =
          (SW == BLANK) * (ES == BLANK) * (MAP[cur_row + 2][cur_col] == BLANK);
      break;
    case 'd':
      b_forward =
          (NE == BLANK) * (ES == BLANK) * (MAP[cur_row][cur_col + 2] == BLANK);
      break;
    default:
      b_forward = false;
  }
  return b_forward;
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

char Tank::getDirection() { return cur_dir; }

int Tank::getBiuColNum() {
  switch (cur_dir) {
    case 'w':
      return cur_col;
    case 's':
      return cur_col;
    case 'a':
      return cur_col - 2;
    case 'd':
      return cur_col + 2;
    default:
      return 0;
  }
}

int Tank::getBiuRowNum() {
  switch (cur_dir) {
    case 'w':
      return cur_row - 2;
    case 's':
      return cur_row + 2;
    case 'a':
      return cur_row;
    case 'd':
      return cur_row;
    default:
      return 27;
  }
}

bool Tank::checkWinning() {
  switch (cur_dir) {
    case 'w':
      return (WN == STAR) || (NE == STAR);
    case 's':
      return (SW == STAR) || (ES == STAR);
    case 'a':
      return (WN == STAR) || (ES == STAR);
    case 'd':
      return (NE == STAR) || (ES == STAR);
    default:
      return false;
  }
}
