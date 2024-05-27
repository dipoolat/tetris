#include "../tetris.h"
//Эта функция проверяет игровое поле  на наличие полностью заполненных 
//линий и очищает их, сдвигая все вышележащие линии вниз.
int clear_lines(cell_t field[][WIDTH]) {
  int total_cleared = 0;
  for (int i = 0; i < HEIGHT; i++) {
    int total_filled = 0;
    for (int j = 0; j < WIDTH; j++) {
      total_filled += field[i][j].value;
    }
    if (total_filled == WIDTH) {
      move_down(field, i);
      total_cleared++;
    }
  }
  return total_cleared;
}