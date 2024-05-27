#include "../tetris.h"
//Сразу опускает текущую фигуру вниз до столкновения с дном или другой фигурой.
//Цикл `while` работает, пока не произойдет столкновение
//Внутри цикла координата `y` текущей фигуры увеличивается на 1, имитируя
//падение.
void quick_fall(game_info_t *gi) {
  if (gi->state != FAST_DOWN)
    return;
  while (!is_collision_y(gi))
    gi->current_figure->y++;
}