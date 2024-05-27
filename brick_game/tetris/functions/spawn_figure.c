#include "../tetris.h"

void spawn_figure(GameInfo_t *gi, pthread_t **thread) {
  if (gi->current_figure != NULL)
    return;
  if (gi->next_figure == NULL) {
    gi->next_figure = calloc(1, sizeof(figure_t));
    create_figure_matrix(gi->next_figure);
  }
  gi->current_figure = gi->next_figure;
  gi->next_figure = calloc(1, sizeof(figure_t));
  create_figure_matrix(gi->next_figure);
  if (*thread != NULL)
    free(*thread);
  *thread = calloc(1, sizeof(pthread_t));
  pthread_create(*thread, NULL, fall_figure, gi);
}