#include "../tetris.h"

void quick_fall(game_info_t *gi) {
  if (gi->state != FAST_DOWN)
    return;
  while (!is_collision_y(gi))
    gi->current_figure->y++;
}