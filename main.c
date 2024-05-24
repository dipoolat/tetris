#include "figure.h"
#include "file_reader.h"
#include <ncurses.h>
#include <pthread.h>
#include <unistd.h>

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

void rotate_figure(figure_t *f) {
  int **temp_matrix = (int **)malloc(f->width * sizeof(int *));
  for (int i = 0; i < f->width; i++) {
    temp_matrix[i] = (int *)malloc(f->height * sizeof(int));
  }
  for (int i = 0; i < f->height; i++) {
    for (int j = 0; j < f->width; j++) {
      temp_matrix[j][f->height - 1 - i] = f->matrix[i][j];
    }
  }
  for (int i = 0; i < f->height; i++) {
    free(f->matrix[i]);
  }
  free(f->matrix);
  int temp = f->height;
  f->height = f->width;
  f->width = temp;
  f->matrix = temp_matrix;
//   f->y += f->height / 2;
}

void s21_transpose(figure_t *f);
void render(int field[][WIDTH], figure_t *f, int score, int h_score);
void move_figure(figure_t *f, int direction, int field[][WIDTH]);
int is_collision_y(int field[][WIDTH], figure_t *f);
int is_collision_x(int field[][WIDTH], figure_t *f, int dir);
int clear_lines(int field[][WIDTH]);

int is_collision_y(int field[][WIDTH], figure_t *f) {
  for (int i = 0; i < f->height; i++) {
    for (int j = 0; j < f->width; j++) {
      if ((field[f->y + i + 1][f->x + j] + f->matrix[i][j] == 2) ||
          (f->y + f->height >= HEIGHT))
        return 1;
    }
  }
  return 0;
}

int is_collision_x(int field[][WIDTH], figure_t *f, int dir) {
  for (int i = 0; i < f->height; i++) {
    for (int j = 0; j < f->width; j++) {
      if (field[f->y + i][f->x + j + dir] + f->matrix[i][j] == 2)
        return 1;
    }
  }
  return 0;
}

void *fall_figure(void *f) {
  while (((figure_t *)f)->y + ((figure_t *)f)->height < HEIGHT) {
    ((figure_t *)f)->y++;
    sleep(1);
  }
}

int main(void) {
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(0);
  timeout(500);
  int filed[HEIGHT][WIDTH] = {0};
  int h_score = get_high_score();
  int score = 0;
  pthread_t *thread = NULL;
  figure_t *f = NULL;
  while (1) {

    if (f == NULL) {
      thread = calloc(1, sizeof(pthread_t));
      f = calloc(1, sizeof(figure_t));
      create_figure_matrix(f);
      pthread_create(thread, NULL, fall_figure, f);
    }
    render(filed, f, score, h_score);
    refresh();
    switch (getch()) {
    case KEY_LEFT:
      move_figure(f, -1, filed);
      break;
    case KEY_RIGHT:
      move_figure(f, 1, filed);
      break;
    case KEY_DOWN:
      break;
    case 'r':
    case KEY_UP:
      rotate_figure(f);
      if (is_collision_y(filed, f) || f->x + f->width > WIDTH) {
        for (int i = 0; i < 3; i++) {
            rotate_figure(f);
        }
      }
      break;
    }

    if (is_collision_y(filed, f)) {
      pthread_cancel(*thread);
      for (int i = 0; i < f->height; i++) {
        for (int j = 0; j < f->width; j++) {
          if (f->matrix[i][j])
            filed[i + f->y][j + f->x] = f->matrix[i][j];
        }
      }
      delete_figure(f);
      free(thread);
      f = NULL;
      thread = NULL;
    }
    score += clear_lines(filed);
    if (score > h_score)
        set_high_score(score);
    erase(); // очистить экран
  }
  endwin();
  return 0;
}

void move_figure(figure_t *f, int direction, int field[][WIDTH]) {
  if (f->x + direction >= 0 && f->x + direction + f->width <= WIDTH && !is_collision_x(field, f, direction)) {
    f->x += direction;
  }
}

void render(int field[][WIDTH], figure_t *f, int score, int h_score) {
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
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (temp_field[i][j]) {
        mvaddch(i, j * 2, '#'); // рисовать фигуру
      } else {
        mvaddch(i, j * 2, '-'); // пустое пространство
      }
    }
  }
  for (int i = 0; i < f->height; i++) {
    for (int j = 0; j < f->width; j++) {
      mvaddch(i + 10, j + 50, f->matrix[i][j] ? '#' : ' ');
    }
  }
  curs_set(120);
  printw("\tscore: %d", score);
  printw("\thigh score: %d", h_score);
  curs_set(0);
}

void move_down(int field[][WIDTH], int line) {
    for (int i = line; i > 0; i--) {
        for (int j = 0; j < WIDTH; j++) {
            field[i][j] = field[i - 1][j];
        }
    }
}

int clear_lines(int field[][WIDTH]) {
    int total_cleared = 0;
    for (int i = 0; i < HEIGHT; i++) {
        int total_filled = 0;
        for (int j = 0; j < WIDTH; j++) {
            total_filled += field[i][j];
        }
        if (total_filled == WIDTH) {
            move_down(field, i);
            total_cleared++;
        }
    }
    return total_cleared;
}