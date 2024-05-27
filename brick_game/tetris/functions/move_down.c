#include "../tetris.h"

void move_down(cell_t field[][WIDTH], int line) {
  for (int i = line; i > 0; i--) {
    for (int j = 0; j < WIDTH; j++) {
      field[i][j] = field[i - 1][j];
      usleep(1000);
    }
  }
}
