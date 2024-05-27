#include "../tetris.h"

int is_collision_y(GameInfo_t *gi) {
  for (int i = 0; i < gi->current_figure->height; i++) {
    for (int j = 0; j < gi->current_figure->width; j++) {
      if ((gi->game_field[gi->current_figure->y + i + 1]
                         [gi->current_figure->x + j]
                             .value +
               gi->current_figure->matrix[i][j] ==
           2) ||
          (gi->current_figure->y + gi->current_figure->height >= HEIGHT))
        return 1;
    }
  }
  return 0;
}