#include "../../brick_game/tetris/tetris.h"
//Обновляет отображение игрового поля на экране.
void render(game_info_t *gi) {
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
