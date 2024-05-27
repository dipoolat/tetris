#include "../tetris.h"

void take_pause(GameInfo_t *gi) {
  if (gi->state == PAUSE)
    gi->pause = !gi->pause;
}