#include "../tetris.h"

void gain_score(GameInfo_t *gi) {
  gi->score += calculate_score(clear_lines(gi->game_field));
  if (gi->score > gi->high_score)
    set_high_score(gi->score);
  gi->level = gi->score / 600 + 1;
  if (gi->level > 10)
    gi->level = 10;
}