#include "../tetris.h"
//Эта функция реализует падение фигуры вниз. Она выполняется в отдельном потоке
//Цикл `while` работает, пока не произойдет 
//столкновение фигуры с дном или другой фигурой
void *fall_figure(void *gi) {
  game_info_t *info = (game_info_t *)gi;
  while (!is_collision_y(info)) {
    if (info->pause)
      continue;
    info->current_figure->y++;
    usleep(info->delay / info->level);
  }
  return NULL;
}