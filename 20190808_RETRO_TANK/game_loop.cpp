#include "game_loop.h"
#include <time.h>

bool GameLoop::checkWinning() { return false; }

GameLoop::GameLoop() {
  // Print jobs.
  g_frame.printFrame();
  col_row_num = g_frame.printMap();
  // Player settings.
  initPlayers();
  // Tank settings.
  initTanks();
}

void GameLoop::initPlayers() {
  // Human player p_1
  Player p_1;
  p_1.setTankGun(gun_a);
  p_1.setTankColNum(col_row_num / FACTOR_MID);
  p_1.setTankRowNum(col_row_num % FACTOR_MID);
  p_1.setAutoOperator(false);
  v_player.push_back(p_1);

  // Robort player p_2
  Player p_2;
  p_2.setTankGun(gun_b);
  p_2.setTankColNum(COLS - (col_row_num / FACTOR_MID));
  p_2.setTankRowNum(col_row_num % FACTOR_MID);
  p_2.setAutoOperator(true);
  v_player.push_back(p_2);
}

void GameLoop::initTanks() {
  for (vector<Player>::iterator it_p = v_player.begin(); it_p != v_player.end();
       it_p++) {
    Tank tk_temp((*it_p).b_robort, (*it_p).tank_dir, (*it_p).tank_col,
                 (*it_p).tank_row, (*it_p).tank_speed, (*it_p).tank_gun,
                 (*it_p).biu_max, (*it_p).biu_speed, (*it_p).biu_type);
    v_tank.push_back(tk_temp);
  }
}

void GameLoop::mainLoop() {
  char kb = '?';  // keyboard listener
  do {
    for (vector<Tank>::iterator it_t = v_tank.begin(); it_t != v_tank.end();
         it_t++) {
      ///////////// Check Tank's Borders /////////////
      (*it_t).checkBorders();
      ///////////// Handle Tank's Bullets /////////////
      if (!(*it_t).v_biu.empty()) {
        // Iterate bullets.
        for (vector<Biu>::iterator it_b = (*it_t).v_biu.begin();
             it_b != (*it_t).v_biu.end();) {
          if ((*it_b).hitTank()) {
            ///////////// Handle Winning /////////////
            goto END;
          } else {
            if ((*it_b).isAlife()) {
              (*it_b).autoFly();
              it_b++;
            } else {
              it_b = (*it_t).v_biu.erase(it_b);
            }
          }
        }
      }
      if (!(*it_t).isRobort()) {
        ///////////// Handle Human Input /////////////
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
  } while (kb != 'p');

END:
  gotoxy(MARGIN_LEFT, MARGIN_BASELINE + 1);
  system("pause");
}
