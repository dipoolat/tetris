#include "../../../brick_game/tetris/tetris.h"

void render_hello() {

  char title[][100] =  {
    "###### ##### ###### #####  #### #####",
    "###### ##### ###### ## ##  #### #####",
    "  ##   ##      ##   ## ##   ##  ##   ",
    "  ##   #####   ##   #####   ##  #####",
    "  ##   ##      ##   ## #    ##     ##",
    "  ##   #####   ##   ## ##   ##  #####",
    "  ##   #####   ##   ##  ## #### #####",
  };

  char instructions[] = "Press any key to start!";
  int y, x;
  getmaxyx(stdscr, y, x);
  for (int i = 0;  i < 6; i++) {
  mvprintw(y / 2 + i, x / 2 - strlen(title[i]) / 2, "%s\n", title[i]);
  }
  mvprintw(y - 3, x / 2 - strlen(instructions) / 2, "%s\n", instructions);
  timeout(-1);
  getch();
  timeout(100);
}