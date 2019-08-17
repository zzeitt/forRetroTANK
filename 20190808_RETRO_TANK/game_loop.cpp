#include "game_loop.h"
#include <time.h>

bool GameLoop::checkWinning() { return false; }

GameLoop::GameLoop() {
  // Print jobs.
  g_frame.printFrame();
  unsigned int trick_num = g_frame.printMap();
  // Player settings.
  Player p_1, p_2;
  p_1.setTankGun(gun_a);
  p_1.setTankColNum(trick_num / FACTOR_MID);
  p_1.setTankRowNum(trick_num % FACTOR_MID);
  p_1.setAutoOperator(false);
  p_2.setTankGun(gun_b);
  p_2.setTankColNum(COLS - (trick_num / FACTOR_MID));
  p_2.setTankRowNum(trick_num % FACTOR_MID);
  p_2.setAutoOperator(true);
  v_player.push_back(p_1);
  v_player.push_back(p_2);
  // Tank settings.
  Tank tk_1(p_1.b_robort, p_1.tank_dir, p_1.tank_col, p_1.tank_row,
            p_1.tank_speed, p_1.tank_gun, p_1.biu_max, p_1.biu_speed,
            p_1.biu_type);
  Tank tk_2(p_2.b_robort, p_2.tank_dir, p_2.tank_col, p_2.tank_row,
            p_2.tank_speed, p_2.tank_gun, p_2.biu_max, p_2.biu_speed,
            p_2.biu_type);
  v_tank.push_back(tk_1);
  v_tank.push_back(tk_2);
}

void GameLoop::mainLoop() {
  char kb = '?';  // keyboard listener
  do {
    if (!checkWinning()) {
      for (vector<Tank>::iterator it_t = v_tank.begin(); it_t != v_tank.end();
           it_t++) {
        ///////////// Check Tank's Borders /////////////
        (*it_t).checkBorders();
        ///////////// Handle Tank's Bullets /////////////
        if (!(*it_t).v_biu.empty()) {
          // Iterate bullets.
          for (vector<Biu>::iterator it_b = (*it_t).v_biu.begin();
               it_b != (*it_t).v_biu.end();) {
            if ((*it_b).isAlife()) {
              (*it_b).autoFly();
              it_b++;
            } else {
              it_b = (*it_t).v_biu.erase(it_b);
            }
          }
        }
        if (!(*it_t).isRobort()) {
          ///////////// Handle Input /////////////
          if (_kbhit()) {
            kb = _getch();
            if (kb == 'j') {
              if ((*it_t).v_biu.size() <= (*it_t).biu_max) {
                Biu biu_temp((*it_t).getDirection(), (*it_t).getBiuColNum(),
                             (*it_t).getBiuRowNum(), (*it_t).biu_speed,
                             (*it_t).biu_type);
                (*it_t).v_biu.push_back(biu_temp);
              }
            }
            if (kb == 'w' || 'a' || 's' || 'd') {
              (*it_t).move(kb);
            }
          } else {  // If no _kbhit().
            gotoxy(MARGIN_LEFT, MARGIN_BASELINE);
          }
        } else {
          ///////////// Handle Robort /////////////
          srand(time(NULL));
          int i_rand = rand() % 5;
          switch (i_rand) {
            case 0:
              break;
            case 1:
              (*it_t).move('w');
              break;
            case 2:
              (*it_t).move('a');
              break;
            case 3:
              (*it_t).move('s');
              break;
            case 4:
              (*it_t).move('d');
              break;
            default:
              break;
          }
        }
      }
    } else {  // If won.
      break;
    }
  } while (kb != 'p');
  gotoxy(MARGIN_LEFT, MARGIN_BASELINE + 1);
  system("pause");
}
