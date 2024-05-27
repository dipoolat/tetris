#include "../tetris.h"
//проверяет, происходит ли столкновение текущей фигуры с левой или правой границей игрового поля или с другими фигурами при движении по горизонтали.
//`dir`: Направление движения: -1 для движения влево, 1 для движения вправо.
int is_collision_x(game_info_t *gi, int dir) {
  for (int i = 0; i < gi->current_figure->height; i++) {
    for (int j = 0; j < gi->current_figure->width; j++) {
      if (gi->game_field[gi->current_figure->y + i]
                        [gi->current_figure->x + j + dir]
                            .value +
              gi->current_figure->matrix[i][j] ==
          2)
        return 1;
    }
  }
  return 0;
}