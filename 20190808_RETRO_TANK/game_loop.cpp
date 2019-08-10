#include "game_loop.h"

GameLoop::GameLoop() {
  g_frame.printFrame();
  g_frame.printMap();
  Tank tk;
  char kb = '?';
  do {
    if (!tk.checkWinning()) {
      if (_kbhit()) {
        kb = _getch();
        if (kb == 'j') {
          // Biusound;
          tk.animateBiu(fast);
        } else {
          tk.move(kb);
        }
      } else {
        gotoxy(0, 26);
      }
    } else {
      break;
    }
  } while (kb != 'p');
  gotoxy(0, 27);
  system("pause");
}
