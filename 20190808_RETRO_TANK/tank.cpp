#include "tank.h"

void Tank::printChar(double col, double row, string str) {
  gotoxy(2 * col, row + MARGIN_UP);
  cout << str;
}

void Tank::printBlock(double col, double row) { printChar(col, row, "¨€"); }

void Tank::printBlank(double col, double row) { printChar(col, row, "  "); }

void Tank::printStar(double col, double row) { printChar(col, row, "¡ï"); }

void Tank::printBiu(double col, double row) {
  printChar(col, row, biu_type.ws_biu);
}

Tank::Tank() {
  cur_dir = 'w';
  cur_col = 20;
  cur_row = 9;
  speed = veryfast;
  gun_type = gun_a;
  biu_type = biu_a;
  printTank();
}

Tank::Tank(char ch_dir, int c, int r, EnumSpeed v, GunType gun, BiuType biu) {
  cur_dir = ch_dir;
  cur_col = c;
  cur_row = r;
  speed = v;
  gun_type = gun;
  biu_type = biu;
  printTank();
}

void Tank::printTank() {
  Sleep(200 - speed);
  printBlock(cur_col, cur_row);
  switch (cur_dir) {
    case 'w':
    case 's':
      printChar(cur_col - 1, cur_row, "©¯");
      printChar(cur_col + 1, cur_row, "©¯");
      switch (cur_dir) {
        case 'w':
          printChar(cur_col, cur_row - 1, gun_type.ws_gun);
          break;
        case 's':
          printChar(cur_col, cur_row + 1, gun_type.ws_gun);
          break;
      }
      break;
    case 'a':
    case 'd':
      printChar(cur_col, cur_row - 1, "¡­");
      printChar(cur_col, cur_row + 1, "¡­");
      switch (cur_dir) {
        case 'a':
          printChar(cur_col - 1, cur_row, gun_type.ad_gun);
          break;
        case 'd':
          printChar(cur_col + 1, cur_row, gun_type.ad_gun);
          break;
      }
      break;
  }
}

void Tank::eraseTank() {
  Sleep(200 - speed);
  printBlank(cur_col, cur_row);
  switch (cur_dir) {
    case 'w':
    case 's':
      printChar(cur_col - 1, cur_row, "  ");
      printChar(cur_col + 1, cur_row, "  ");
      switch (cur_dir) {
        case 'w':
          printChar(cur_col, cur_row - 1, "  ");
          break;
        case 's':
          printChar(cur_col, cur_row + 1, "  ");
          break;
      }
      break;
    case 'a':
    case 'd':
      printChar(cur_col, cur_row - 1, "  ");
      printChar(cur_col, cur_row + 1, "  ");
      switch (cur_dir) {
        case 'a':
          printChar(cur_col - 1, cur_row, "  ");
          break;
        case 'd':
          printChar(cur_col + 1, cur_row, "  ");
          break;
      }
      break;
  }
}

void Tank::printWin() {}

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
  }
  return b_forward;
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
  }
}

void Tank::move(char dst_dir) {
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
    }
  } else {
    if (dst_dir == 'w' || dst_dir == 'a' || dst_dir == 's' || dst_dir == 'd') {
      if (checkTurning(dst_dir)) {
        eraseTank();
        cur_dir = dst_dir;
        printTank();
      }
    }
  }
  if (checkWinning()) {
    printWin();
  }
}

void Tank::animateBiu(EnumSpeed biuspeed) {
  bool mark = 1;
  switch (cur_dir) {
    case 'w':
    case 's':
      switch (cur_dir) {
        case 'w':
          for (int r = cur_row - 2; (r > 0) && mark; r--) {
            printBiu(cur_col, r);
            switch (MAP[r][cur_col]) {
              case BLOCK:
                Sleep(200 - biuspeed);
                printBlank(cur_col, r);
                MAP[r][cur_col]++;
                mark = 0;
                break;
              case WALL:
                printBlock(cur_col, r);
                MAP[r][cur_col]++;
                mark = 0;
                break;
              case BLANK:
                Sleep(200 - biuspeed);
                printBlank(cur_col, r);
                break;
              case STAR:
                printStar(cur_col, r);
                mark = 0;
                break;
            }
          }
          break;
        case 's':
          for (int r = cur_row + 2; (r < 19) && mark; r++) {
            printBiu(cur_col, r);
            switch (MAP[r][cur_col]) {
              case BLOCK:
                Sleep(200 - biuspeed);
                printBlank(cur_col, r);
                MAP[r][cur_col]++;
                mark = 0;
                break;
              case WALL:
                printBlock(cur_col, r);
                MAP[r][cur_col]++;
                mark = 0;
                break;
              case BLANK:
                Sleep(200 - biuspeed);
                printBlank(cur_col, r);
                break;
              case STAR:
                printStar(cur_col, r);
                mark = 0;
                break;
            }
          }
          break;
      }
      break;
    case 'a':
    case 'd':
      switch (cur_dir) {
        case 'a':
          for (int c = cur_col - 2; (c > 0) && mark; c--) {
            printBiu(c, cur_row);
            switch (MAP[cur_row][c]) {
              case BLOCK:
                Sleep(200 - biuspeed);
                printBlank(c, cur_row);
                MAP[cur_row][c]++;
                mark = 0;
                break;
              case WALL:
                printBlock(c, cur_row);
                MAP[cur_row][c]++;
                mark = 0;
                break;
              case BLANK:
                Sleep(200 - biuspeed);
                printBlank(c, cur_row);
                break;
              case STAR:
                printStar(c, cur_row);
                mark = 0;
                break;
            }
          }
          break;
        case 'd':
          for (int c = cur_col + 2; (c < 43) && mark; c++) {
            printBiu(c, cur_row);
            switch (MAP[cur_row][c]) {
              case BLOCK:
                Sleep(200 - biuspeed);
                printBlank(c, cur_row);
                MAP[cur_row][c]++;
                mark = 0;
                break;
              case WALL:
                printBlock(c, cur_row);
                MAP[cur_row][c]++;
                mark = 0;
                break;
              case BLANK:
                Sleep(200 - biuspeed);
                printBlank(c, cur_row);
                break;
              case STAR:
                printStar(c, cur_row);
                mark = 0;
                break;
            }
          }
          break;
      }
      break;
  }
}
