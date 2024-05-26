#include "../tetris.h"

int game_over(game_info_t *gi) {
  return gi->current_figure->y == 0 && is_collision_y(gi);
}