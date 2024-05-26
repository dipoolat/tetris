#include "../../../brick_game/tetris/tetris.h"

void render_side_panel(game_info_t *gi) {
  mvprintw(1, 35, "SCORE: %d", gi->score);
  mvprintw(2, 35, "BEST SCORE: %d", gi->high_score);
  mvprintw(3, 35, "LVL: %d", gi->level);
  if (gi->pause) {
    attron(COLOR_PAIR(8));
    mvprintw(8, 35, "PAUSED");
    attron(COLOR_PAIR(8));
  }
}