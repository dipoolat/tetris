#include "figure.h"
#include <unistd.h>
#include <ncurses.h>
#include <pthread.h>

typedef enum {
    PAUSE, 
    LEFT, 
    RIGHT, 
    DOWN, 
    FAST_DOWN, 
    TERMINMATE, 
    ROTATE 
} game_states_t;

#define UNUSED(x) ((void)(x))

void s21_transpose(figure_t *f);
void render(int field[][WIDTH], figure_t* f);
void move_figure(figure_t* f, int direction);
int is_collision(int field[][WIDTH], figure_t* f);

int is_collision(int field[][WIDTH], figure_t* f) {
    for (int i = 0; i < f->height; i++) {
        for (int j = 0; j < f->width; j++) {
            if ((field[f->y + i][f->x + j] + f->matrix[i][j] == 2) ||
                (f->y + f->height == HEIGHT))
                return 1;
        }
    }
    return 0;
}

void* fall_figure(void* f) {
  while (((figure_t*)f)->y + ((figure_t*)f)->height < HEIGHT) {
    ((figure_t*)f)->y++;
    sleep(1);
  }
}

//FIXME
int main(void) {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(500);
    int filed[HEIGHT][WIDTH] = {0};
    pthread_t* thread = NULL;
    figure_t* f = NULL;
    while (1) {

        if (f == NULL) {
            thread = calloc(1, sizeof(pthread_t));
            f = calloc(1, sizeof(figure_t));
            create_figure_matrix(f);
            printw("\n%d\n", f->height);
            pthread_create(thread, NULL, fall_figure, f);
        }
        render(filed, f);
        refresh();
        switch (getch()) {
            case KEY_LEFT:
                move_figure(f, -1);
                break;
            case KEY_RIGHT:
                move_figure(f, 1);
                break;
            case KEY_DOWN:
                break;
            case 't':
                s21_transpose(f);
                break;
        }

        if (is_collision(filed, f)) {
          pthread_cancel(*thread);
          for (int i = 0; i < f->height; i++) {
            for (int j = 0; j < f->width; j++) {
              filed[i + f->y][j + f->x] = f->matrix[i][j];
            }
          }
          delete_figure(f);
          free(thread);
          f = NULL;
          thread = NULL;
        }
    }
    endwin();
    return 0;
}

void move_figure(figure_t* f, int direction) {
    if (f->x + direction >= 0 && f->x + direction + f->width <= WIDTH) {
        f->x += direction;
    }
}

void render(int field[][WIDTH], figure_t* f) {
    int temp_field[HEIGHT][WIDTH] = {0};
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            temp_field[i][j] = field[i][j];
        }
    }
    for (int i = 0; i < f->height; i++) {
        for (int j = 0; j < f->width; j++) {
            if (f->matrix[i][j]) {
                temp_field[f->y + i][f->x + j] = 1; 
            }
        }
    }
    erase(); // очистить экран
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (temp_field[i][j]) {
                mvaddch(i, j * 2, '#'); // рисовать фигуру
            } else {
                mvaddch(i, j * 2, '-'); // пустое пространство
            }
        }
    }
}

void s21_transpose(figure_t *f) {
    int ** result = calloc(f->width, sizeof(int*));
    for(int i=0; i<f->width; i++)
    {
        result[i]=calloc(f->height, sizeof(int));
    }
    for (int i = 0; i < f->height; i++) {
      for (int j = 0; j < f->width; j++) {
        result[i][j] = f->matrix[i][j];
      }
    }
  delete_figure(f);
    int width_1 = f->width;
    f->width= f->height;
    f->height = width_1;
    f->matrix= result;
}
