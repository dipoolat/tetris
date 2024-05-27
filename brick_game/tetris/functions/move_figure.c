#include "../tetris.h"
//Перемещает текущую фигуру влево или вправо.
// gi->state`: Текущее состояние игры (LEFT - влево, RIGHT - вправо)
//Если текущее состояние не является LEFT или RIGHT
//или игра находится на паузе, функция ничего не делает.
void move_figure(game_info_t *gi) {
  if ((gi->state != LEFT && gi->state != RIGHT) || gi->pause)
    return;
  int direction = gi->state == LEFT ? -1 : 1;
  if (gi->current_figure->x + direction >= 0 &&
      gi->current_figure->x + direction + gi->current_figure->width <= WIDTH &&
      !is_collision_x(gi, direction)) {
    gi->current_figure->x += direction;
  }
}