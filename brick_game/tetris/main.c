#include "tetris.h"
//точка входа
int main(void) {

  init_ncurses();

  pthread_t *thread = NULL;
  game_info_t gi = {0};
  gi.high_score = get_high_score();
  gi.delay = 1000000;
  gi.level = 1;

  int running = 1;

  while (running) {
    spawn_figure(&gi, &thread);
    running = !game_over(&gi);
    render(&gi);
    gi.state = get_current_state();
    take_pause(&gi);
    if (gi.pause)
      continue;
    quick_fall(&gi);
    move_figure(&gi);
    rotate_figure(&gi);
    restore_rotate(&gi);
    terminate_figure(&gi, &thread);
    gain_score(&gi);
    erase(); // очистить экран
  }

  erase();

  terminate_game(&gi);
  recall(&gi, thread);

  return 0;
}