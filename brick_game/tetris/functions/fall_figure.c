#include "../tetris.h"

void *fall_figure(void *gi) {
  game_info_t *info = (game_info_t *)gi;
  while (!is_collision_y(info)) {
    if (info->pause)
      continue;
    info->current_figure->y++;
    usleep(info->delay / info->level);
  }
  return NULL;
}