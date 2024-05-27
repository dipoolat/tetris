#include "tetris.h"

/**
 * @brief Обрабатывает ввод пользователя
 * @param action Действие пользователя
 * @param hold Зажата ли клавиша
*/
void userInput(UserAction_t action, bool hold);

/**
 * @brief Обновляет состояние игры
 * @return Возвращает измененнную структуру конфигурации
*/
GameInfo_t updateCurrentState();

/**
 * @brief Функция хранит синглтон
 * @return Возвращает синглтон
*/
GameInfo_t *get_singleton() {
  static GameInfo_t singleton = {0};
  return &singleton;
}

GameInfo_t updateCurrentState() {
  GameInfo_t* gi = get_singleton();
  gain_score(gi);
  return *gi;
}

void userInput(UserAction_t action, bool hold) {
  UNUSED(hold);
  switch (action) {
  case PAUSE:
    take_pause(get_singleton());
    break;
  case FAST_DOWN:
    quick_fall(get_singleton());
    break;
  case LEFT:
  case RIGHT:
    move_figure(get_singleton());
    break;
  case ROTATE:
    rotate_figure(get_singleton());
    restore_rotate(get_singleton());
    break;
  default:
  break;
  }
}

/**
 * @brief Точка входа
 */
int main(void) {

  init_ncurses();

  pthread_t *thread = NULL;
  GameInfo_t* gi = get_singleton();
  gi->high_score = get_high_score();
  gi->speed = 1000000;
  gi->level = 1;

  int running = 1;

  while (running) {
    spawn_figure(gi, &thread);
    running = !game_over(gi);
    render(gi);
    gi->state = get_current_state();
    userInput(gi->state, 0);
    if (gi->pause)
      continue;
    terminate_figure(gi, &thread);
    gain_score(gi);
    erase(); // очистить экран
  }

  erase();

  terminate_game(gi);
  recall(gi, thread);

  return 0;
}