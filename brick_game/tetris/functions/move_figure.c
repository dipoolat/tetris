#include "../tetris.h"

void move_figure(GameInfo_t *gi) {
  if ((gi->state != LEFT && gi->state != RIGHT) || gi->pause)
    return;
  int direction = gi->state == LEFT ? -1 : 1;
  if (gi->current_figure->x + direction >= 0 &&
      gi->current_figure->x + direction + gi->current_figure->width <= WIDTH &&
      !is_collision_x(gi, direction)) {
    gi->current_figure->x += direction;
  }
}