#include "../tetris.h"

void init_ncurses() {
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(0);
  timeout(100);
  start_color();
  init_pair(0, COLOR_BLACK, COLOR_BLACK);
  init_pair(1, COLOR_BLACK, COLOR_BLUE);
  init_pair(2, COLOR_BLACK, COLOR_CYAN);
  init_pair(3, COLOR_BLACK, COLOR_GREEN);
  init_pair(4, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(5, COLOR_BLACK, COLOR_RED);
  init_pair(6, COLOR_BLACK, COLOR_YELLOW);
  init_pair(7, COLOR_BLACK, COLOR_WHITE);
  init_pair(8, COLOR_RED, COLOR_BLACK);
}