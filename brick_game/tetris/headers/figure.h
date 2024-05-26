#ifndef _FIGURE_H

#define _FIGURE_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int x;
  int y;
  int **matrix;
  int height;
  int width;
  int color_pair;
} figure_t;

void create_figure_matrix(figure_t *f);
void delete_figure(figure_t *f);

#endif //_FIGURE_H
