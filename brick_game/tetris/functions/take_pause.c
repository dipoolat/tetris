#include "../tetris.h"
//Переключает состояние паузы игры.
//Если `gi->state` равно PAUSE, значение `gi->pause`
// инвертируется (меняется на противоположное).
void take_pause(game_info_t *gi) {
  if (gi->state == PAUSE)
    gi->pause = !gi->pause;
}