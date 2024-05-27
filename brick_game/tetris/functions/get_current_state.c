#include "../tetris.h"
//функция получает текущее действие пользователя (направление движения, вращение, пауза).
//Используется функция `getch()`, чтобы получить символ, введенный пользователем.
game_state_t get_current_state() {
  game_state_t action = DOWN;
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