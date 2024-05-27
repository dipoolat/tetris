#include "../tetris.h"

void quick_fall(GameInfo_t *gi) {
  if (gi->state != FAST_DOWN || gi->pause)
    return;
  while (!is_collision_y(gi))
    gi->current_figure->y++;
}