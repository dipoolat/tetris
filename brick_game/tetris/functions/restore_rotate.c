#include "../tetris.h"

void restore_rotate(GameInfo_t *gi) {
  if (is_collision_y(gi) ||
      gi->current_figure->x + gi->current_figure->width > WIDTH) {
    for (int i = 0; i < 3; i++) {
      rotate_figure(gi);
    }
  }
}