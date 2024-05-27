#include "../tetris.h"

void *fall_figure(void *gi) {
  GameInfo_t *info = (GameInfo_t *)gi;
  while (!is_collision_y(info)) {
    if (info->pause)
      continue;
    info->current_figure->y++;
    usleep(info->speed / info->level);
  }
  return NULL;
}