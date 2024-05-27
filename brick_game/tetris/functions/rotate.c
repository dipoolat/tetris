#include "../tetris.h"
//Вращает текущую фигуру против часовой стрелки.
//Если `gi->state` не равно ROTATE, функция ничего не делает
//Высота и ширина фигуры меняются местами
void rotate_figure(game_info_t *gi) {

  if (gi->state != ROTATE)
    return;

  int **temp_matrix = (int **)malloc(gi->current_figure->width * sizeof(int *));
  for (int i = 0; i < gi->current_figure->width; i++) {
    temp_matrix[i] = (int *)malloc(gi->current_figure->height * sizeof(int));
  }
  for (int i = 0; i < gi->current_figure->height; i++) {
    for (int j = 0; j < gi->current_figure->width; j++) {
      temp_matrix[j][gi->current_figure->height - 1 - i] =
          gi->current_figure->matrix[i][j];
    }
  }
  for (int i = 0; i < gi->current_figure->height; i++) {
    free(gi->current_figure->matrix[i]);
  }
  free(gi->current_figure->matrix);
  int temp = gi->current_figure->height;
  gi->current_figure->height = gi->current_figure->width;
  gi->current_figure->width = temp;
  gi->current_figure->matrix = temp_matrix;
}