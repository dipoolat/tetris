#include "../../../brick_game/tetris/tetris.h"

void render_next_figure(game_info_t* gi) {
    for (int i = 0; i < gi->next_figure->height; i++) {
    for (int j = 0; j < gi->next_figure->width; j++) {
      if (gi->next_figure->matrix[i][j]) {
        attron(COLOR_PAIR(gi->next_figure->color_pair));
        mvprintw(5 + i, 35 + j, "%2s", " ");
        attroff(COLOR_PAIR(gi->next_figure->color_pair));
      }
    }
  }
}