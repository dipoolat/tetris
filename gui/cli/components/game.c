#include "../../../brick_game/tetris/tetris.h"
//Отрисовывает игровое поле на экране.
void render_game(cell_t t[HEIGHT][WIDTH]) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      attron(COLOR_PAIR(t[i][j].color_pair));
      printw("%3c", ' ');
      attroff(COLOR_PAIR(t[i][j].color_pair));
    }
    printw("\n");
  }
}