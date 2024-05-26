#include "headers/figure.h"

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

const int matrix_6[][3] = {
    {1, 0, 0},
    {1, 1, 1},
};

const int matrix_7[][3] = {
    {1, 1, 0},
    {0, 1, 1},
};

void create_figure_matrix(figure_t *f) {
  srand(time(NULL));
  int matrix_type = (float)((float)rand() / RAND_MAX) * 7;
  switch (matrix_type) {
  case 0:
    f->color_pair = 1;
    f->width = 2;
    f->height = 2;
    f->matrix = calloc(2, sizeof(int *));
    for (int i = 0; i < 2; i++) {
      f->matrix[i] = calloc(2, sizeof(int));
      for (int j = 0; j < 2; j++) {
        f->matrix[i][j] = 1;
      }
    }
    break;
  case 1:
    f->color_pair = 2;
    f->width = 3;
    f->height = 2;
    f->matrix = calloc(2, sizeof(int *));
    for (int i = 0; i < 2; i++) {
      f->matrix[i] = calloc(3, sizeof(int));
      for (int j = 0; j < 3; j++) {
        f->matrix[i][j] = matrix_2[i][j];
      }
    }
    break;
  case 2:
    f->color_pair = 3;
    f->width = 3;
    f->height = 2;
    f->matrix = calloc(2, sizeof(int *));
    for (int i = 0; i < 2; i++) {
      f->matrix[i] = calloc(3, sizeof(int));
      for (int j = 0; j < 3; j++) {
        f->matrix[i][j] = matrix_3[i][j];
      }
    }
    break;
  case 3:
    f->color_pair = 4;
    f->width = 3;
    f->height = 2;
    f->matrix = calloc(2, sizeof(int *));
    for (int i = 0; i < 2; i++) {
      f->matrix[i] = calloc(3, sizeof(int));
      for (int j = 0; j < 3; j++) {
        f->matrix[i][j] = matrix_4[i][j];
      }
    }
    break;
  case 4:
    f->color_pair = 5;
    f->width = 4;
    f->height = 1;
    f->matrix = calloc(1, sizeof(int *));
    f->matrix[0] = calloc(5, sizeof(int));
    for (int j = 0; j < 4; j++) {
      f->matrix[0][j] = 1;
    }
    break;
  case 5:
    f->color_pair = 6;
    f->width = 3;
    f->height = 2;
    f->matrix = calloc(2, sizeof(int *));
    for (int i = 0; i < 2; i++) {
      f->matrix[i] = calloc(3, sizeof(int));
      for (int j = 0; j < 3; j++) {
        f->matrix[i][j] = matrix_6[i][j];
      }
    }
    break;
  case 6:
    f->color_pair = 7;
    f->width = 3;
    f->height = 2;
    f->matrix = calloc(2, sizeof(int *));
    for (int i = 0; i < 2; i++) {
      f->matrix[i] = calloc(3, sizeof(int));
      for (int j = 0; j < 3; j++) {
        f->matrix[i][j] = matrix_7[i][j];
      }
    }
    break;
  }
}

void delete_figure(figure_t *f) {
  for (int i = 0; i < f->height; i++) {
    free(f->matrix[i]);
  }
  free(f->matrix);
}
