#include "game_loop.h"

GameLoop::GameLoop() {
  g_frame.printFrame();
  g_frame.printMap();
  // Default settings for Tank.
  tank_dir = 'a';
  tank_col = 20;
  tank_row = 9;
  tank_speed = FAST;
  tank_gun = gun_a;
  // Default settings for Bullets.
  biu_max = 5;
  biu_speed = FAST;
  biu_type = biu_a;
}

void GameLoop::setTankSpeed(EnumSpeed v) { tank_speed = v; }

void GameLoop::setBiuSpeed(EnumSpeed v) { biu_speed = v; }

void GameLoop::mainLoop() {
  // Game settings.
  setTankSpeed(FAST);
  setBiuSpeed(MEDIUM);
  // Initialize a tank and a queue of bullets.
  std::vector<Biu> v_biu;
  Tank tk(tank_dir, tank_col, tank_row, tank_speed, tank_gun);
  // Listening keyboard.
  char kb = '?';
  do {
    if (!tk.checkWinning()) {
      ///////////// Handle Bullets /////////////
      if (!v_biu.empty()) {
        for (vector<Biu>::iterator it = v_biu.begin(); it != v_biu.end();) {
          if ((*it).isAlife()) {
            (*it).autoFly();
            it++;
          } else {
            it = v_biu.erase(it);
          }
        }
      }
      ///////////// Handle Input /////////////
      if (_kbhit()) {
        kb = _getch();
        if (kb == 'j') {
          if (v_biu.size() <= biu_max) {
            Biu biu_temp(tk.getDirection(), tk.getBiuColNum(),
                         tk.getBiuRowNum(), biu_speed, biu_type);
            v_biu.push_back(biu_temp);
          }
        }
        if (kb == 'w' || 'a' || 's' || 'd') {
          tk.move(kb);
        }
      } else {  // If no _kbhit().
        gotoxy(MARGIN_LEFT, MARGIN_BASELINE);
      }
      ///////////// Handle Winning /////////////
    } else {  // If won.
      break;
    }
  } while (kb != 'p');
  gotoxy(MARGIN_LEFT, MARGIN_BASELINE + 1);
  system("pause");
}
