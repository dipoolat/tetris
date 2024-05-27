#include "../../brick_game/tetris/tetris.h"
//Добавляет ячейки текущей фигуры в массив игрового поля.
void sum_array(game_info_t *gi, cell_t t[][WIDTH]) {
  for (int i = 0; i < gi->current_figure->height; i++) {
    for (int j = 0; j < gi->current_figure->width; j++) {
      if (gi->current_figure->matrix[i][j]) {
        t[gi->current_figure->y + i][gi->current_figure->x + j].value = 1;
        t[gi->current_figure->y + i][gi->current_figure->x + j].color_pair =
            gi->current_figure->color_pair;
      }
    }
  }
}