#include "../tetris.h"

int game_over(GameInfo_t *gi) {
  return gi->current_figure->y == 0 && is_collision_y(gi);
}