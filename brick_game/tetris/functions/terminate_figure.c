#include "../tetris.h"

void terminate_figure(GameInfo_t *gi, pthread_t **thread) {
  if (is_collision_y(gi)) {
    if (thread != NULL)
      pthread_cancel(**thread);
    for (int i = 0; i < gi->current_figure->height; i++) {
      for (int j = 0; j < gi->current_figure->width; j++) {
        if (gi->current_figure->matrix[i][j]) {
          gi->game_field[i + gi->current_figure->y][j + gi->current_figure->x]
              .value = gi->current_figure->matrix[i][j];
          gi->game_field[i + gi->current_figure->y][j + gi->current_figure->x]
              .color_pair = gi->current_figure->color_pair;
        }
      }
    }
    delete_figure(gi->current_figure);
    free(gi->current_figure);
    if (thread != NULL) {
      free(*thread);
      *thread = NULL;
    }
    gi->current_figure = NULL;
  }
}
