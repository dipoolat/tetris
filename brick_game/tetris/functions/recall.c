#include "../tetris.h"

void recall(GameInfo_t *gi, pthread_t *thread) {
  endwin();

  if (gi->current_figure)
    delete_figure(gi->current_figure);
  if (gi->next_figure)
    delete_figure(gi->next_figure);
  if (thread) {
    pthread_cancel(*thread);
    free(thread);
  }
}
