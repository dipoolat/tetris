#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>

#define WIDTH 10
#define HEIGHT 20


typedef struct {
    int x;
    int y;
    int** matrix;
    int height;
    int width;
} figure_t;

void create_figure_matrix(figure_t* f);
void print_figure(figure_t* f);
void delete_figure(figure_t* f);
