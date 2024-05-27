#include "../../brick_game/tetris/tetris.h"
//Копирует данные из одного двумерного массива
//Внутри циклов значения `value` и `color_pair` из каждой ячейки 
//массива `ar` копируются в соответствующие ячейки массива `t`.
void copy_array(cell_t ar[][WIDTH], cell_t t[][WIDTH]) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      t[i][j].value = ar[i][j].value;
      t[i][j].color_pair = ar[i][j].color_pair;
    }
  }
}