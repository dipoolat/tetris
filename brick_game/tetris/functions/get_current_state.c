#include "../tetris.h"

UserAction_t get_current_state() {
  UserAction_t action = DOWN;
  switch (getch()) {
  case KEY_UP:
  case 'r':
    action = ROTATE;
    break;
  case KEY_DOWN:
    action = FAST_DOWN;
    break;
  case KEY_LEFT:
    action = LEFT;
    break;
  case KEY_RIGHT:
    action = RIGHT;
    break;
  case 'p':
    action = PAUSE;
    break;
  case 'q':
  case 'v':
    erase();
    endwin();
    exit(0);
  }
  return action;
}