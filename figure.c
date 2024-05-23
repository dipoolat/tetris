#include "figure.h"

const int matrix_1[][2] = {
    {1, 1},
    {1, 1},
};

const int matrix_2[][3] = {
    {0, 1, 0},
    {1, 1, 1},
};

const int matrix_3[][3] = {
    {0, 1, 1},
    {1, 1, 0},
};

const int matrix_4[][3] = {
    {0, 0, 1},
    {1, 1, 1},
};

const int matrix_5[][4] = {{1, 1, 1, 1}};

void create_figure_matrix(figure_t *f) {
  srand(time(NULL));
  int type = rand() % 4;
  switch (type) {
  case 0: // Линия
    f->height = 1;
    f->width = 4;
    f->matrix = malloc(f->height * sizeof(int *));
    for (int i = 0; i < f->height; i++) {
      f->matrix[i] = malloc(f->width * sizeof(int));
      for (int j = 0; j < f->width; j++) {
        f->matrix[i][j] = 1;
      }
    }
    break;
  case 1: // Квадрат
    f->height = 2;
    f->width = 2;
    f->matrix = malloc(f->height * sizeof(int *));
    for (int i = 0; i < f->height; i++) {
      f->matrix[i] = malloc(f->width * sizeof(int));
      for (int j = 0; j < f->width; j++) {
        f->matrix[i][j] = 1;
      }
    }
    break;
  case 2: //  L-образная
    f->height = 2;
    f->width = 3;
    f->matrix = malloc(f->height * sizeof(int *));
    f->matrix[0] = malloc(f->width * sizeof(int));
    f->matrix[1] = malloc(f->width * sizeof(int));
    f->matrix[0][0] = 1;
    f->matrix[0][1] = 1;
    f->matrix[0][2] = 1;
    f->matrix[1][2] = 1;
    break;
  case 3: // T-образная
    f->height = 3;
    f->width = 3;
    f->matrix = malloc(f->height * sizeof(int *));
    for (int i = 0; i < f->height; i++) {
      f->matrix[i] = malloc(f->width * sizeof(int));
    }
    f->matrix[0][1] = 1;
    f->matrix[1][0] = 1;
    f->matrix[1][1] = 1;
    f->matrix[1][2] = 1;
    break;
  default:
    break;
  }
  f->x = WIDTH / 2 - f->width / 2;
  f->y = 0;
}

void print_figure(figure_t *f) {
  for (int i = 0; i < f->height; i++) {
    for (int j = 0; j < f->width; j++) {
      printf("%d ", f->matrix[i][j]);
    }
    printf("\n");
  }
}

void delete_figure(figure_t *f) {
  for (int i = 0; i < f->height; i++) {
    free(f->matrix[i]);
  }
  free(f->matrix);
  f->x = 0;
  f->y = 0;
}
