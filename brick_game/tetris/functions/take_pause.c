#include "../tetris.h"

void take_pause(game_info_t *gi) {
  if (gi->state == PAUSE)
    gi->pause = !gi->pause;
}