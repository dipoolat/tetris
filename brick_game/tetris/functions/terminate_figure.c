#include "../tetris.h"
//Завершает падение текущей фигуры, если она столкнулась с дном или другой фигурой
//Если происходит столкновение (`is_collision_y(gi)`), поток, отвечающий за 
//падение фигуры, завершается с помощью `pthread_cancel(**thread)
void terminate_figure(game_info_t *gi, pthread_t **thread) {
  if (is_collision_y(gi)) {
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
    free(*thread);
    gi->current_figure = NULL;
    *thread = NULL;
  }
}
