#include "../../brick_game/tetris/tetris.h"

void render(GameInfo_t *gi) {
  cell_t temp_field[HEIGHT][WIDTH] = {0};
  copy_array(gi->game_field, temp_field);
  sum_array(gi, temp_field);

  erase();
  render_game(temp_field);
  render_border();
  render_side_panel(gi);
  render_next_figure(gi);

  refresh();
}
