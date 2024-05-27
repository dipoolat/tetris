#include "../../../brick_game/tetris/tetris.h"
//Отрисовывает горизонтальную границу в верхней части игрового поля.
void render_border() {
  for (int i = 0; i < WIDTH; i++) {
    attron(COLOR_PAIR(7));
    printw("%3c", ' ');
    attroff(COLOR_PAIR(7));
  }
}