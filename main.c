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
} game_state_t;

typedef struct {
  int color_pair;
  int value;
} cell_t;

typedef struct {
  figure_t *current_figure;
  figure_t *next_figure;
  game_state_t state;
  int score;
  int high_score;
  cell_t game_field[HEIGHT][WIDTH];
  int pause;
  int delay;
  int level;
} game_info_t;

#define UNUSED(x) ((void)(x))

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

game_state_t get_current_state();
void render(game_info_t *gi);
void move_figure(game_info_t *gi);
int is_collision_y(game_info_t *gi);
int is_collision_x(game_info_t *gi, int dir);
int clear_lines(cell_t field[][WIDTH]);

int is_collision_y(game_info_t *gi) {
  for (int i = 0; i < gi->current_figure->height; i++) {
    for (int j = 0; j < gi->current_figure->width; j++) {
      if ((gi->game_field[gi->current_figure->y + i + 1]
                         [gi->current_figure->x + j]
                             .value +
               gi->current_figure->matrix[i][j] ==
           2) ||
          (gi->current_figure->y + gi->current_figure->height >= HEIGHT))
        return 1;
    }
  }
  return 0;
}

void restore_rotate(game_info_t *gi) {
  if (is_collision_y(gi) ||
      gi->current_figure->x + gi->current_figure->width > WIDTH) {
    for (int i = 0; i < 3; i++) {
      rotate_figure(gi);
    }
  }
}

game_state_t get_current_state() {
  game_state_t action = DOWN;
  switch (getch()) {
  case KEY_UP:
  case 'r':
    action = ROTATE;
    break;
  case KEY_DOWN:
    action = FAST_DOWN;
    break;
  case KEY_LEFT:
    action = LEFT;
    break;
  case KEY_RIGHT:
    action = RIGHT;
    break;
  case 'p':
    action = PAUSE;
    break;
  }
  return action;
}

int is_collision_x(game_info_t *gi, int dir) {
  for (int i = 0; i < gi->current_figure->height; i++) {
    for (int j = 0; j < gi->current_figure->width; j++) {
      if (gi->game_field[gi->current_figure->y + i]
                        [gi->current_figure->x + j + dir]
                            .value +
              gi->current_figure->matrix[i][j] ==
          2)
        return 1;
    }
  }
  return 0;
}

void *fall_figure(void *gi) {
  game_info_t *info = (game_info_t *)gi;
  while (!is_collision_y(info)) {
    if (info->pause)
      continue;
    info->current_figure->y++;
    usleep(info->delay);
  }
}

void spawn_figure(game_info_t *gi, pthread_t **thread) {
  if (gi->current_figure != NULL)
    return;
  if (gi->next_figure == NULL) {
    gi->next_figure = calloc(1, sizeof(figure_t));
    create_figure_matrix(gi->next_figure);
  }
  gi->current_figure = gi->next_figure;
  gi->next_figure = calloc(1, sizeof(figure_t));
  create_figure_matrix(gi->next_figure);
  *thread = calloc(1, sizeof(pthread_t));
  pthread_create(*thread, NULL, fall_figure, gi);
}

void init_ncurses() {
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(0);
  timeout(50);
  start_color();
  init_pair(0, COLOR_BLACK, COLOR_BLACK);
  init_pair(1, COLOR_BLACK, COLOR_BLUE);
  init_pair(2, COLOR_BLACK, COLOR_CYAN);
  init_pair(3, COLOR_BLACK, COLOR_GREEN);
  init_pair(4, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(5, COLOR_BLACK, COLOR_RED);
  init_pair(6, COLOR_BLACK, COLOR_YELLOW);
  init_pair(7, COLOR_BLACK, COLOR_WHITE);
}

void terminate_figure(game_info_t *gi, pthread_t **thread) {
  if (is_collision_y(gi)) {
    pthread_cancel(**thread);
    for (int i = 0; i < gi->current_figure->height; i++) {
      for (int j = 0; j < gi->current_figure->width; j++) {
        if (gi->current_figure->matrix[i][j]) {
          gi->game_field[i + gi->current_figure->y][j + gi->current_figure->x]
              .value = gi->current_figure->matrix[i][j];
          gi->game_field[i + gi->current_figure->y][j + gi->current_figure->x]
              .color_pair = gi->current_figure->color_pair;
        }
      }
    }
    delete_figure(gi->current_figure);
    free(*thread);
    gi->current_figure = NULL;
    *thread = NULL;
  }
}

void take_pause(game_info_t *gi) {
  if (gi->state == PAUSE)
    gi->pause = !gi->pause;
}

void gain_score(game_info_t *gi) {
  gi->score += clear_lines(gi->game_field);
  if (gi->score > gi->high_score)
    set_high_score(gi->score);
}

void quick_fall(game_info_t *gi) {
  if (gi->state == FAST_DOWN) {
    gi->delay = 100000;
  } else {
    gi->delay = 1000000;
  }
}

int main(void) {

  init_ncurses();

  pthread_t *thread = NULL;
  game_info_t gi = {0};
  gi.high_score = get_high_score();
  gi.delay = 1000000;
  gi.level = 1;

  while (1) {
    spawn_figure(&gi, &thread);
    render(&gi);
    gi.state = get_current_state();
    take_pause(&gi);
    if (gi.pause)
      continue;
    quick_fall(&gi);
    move_figure(&gi);
    rotate_figure(&gi);
    restore_rotate(&gi);
    terminate_figure(&gi, &thread);
    gain_score(&gi);
    erase(); // очистить экран
  }
  endwin();
  return 0;
}

void move_figure(game_info_t *gi) {
  if ((gi->state != LEFT && gi->state != RIGHT) || gi->pause)
    return;
  int direction = gi->state == LEFT ? -1 : 1;
  if (gi->current_figure->x + direction >= 0 &&
      gi->current_figure->x + direction + gi->current_figure->width <= WIDTH &&
      !is_collision_x(gi, direction)) {
    gi->current_figure->x += direction;
  }
}

void render(game_info_t *gi) {
  cell_t temp_field[HEIGHT][WIDTH] = {0};
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      temp_field[i][j].value = gi->game_field[i][j].value;
      temp_field[i][j].color_pair = gi->game_field[i][j].color_pair;
    }
  }
  for (int i = 0; i < gi->current_figure->height; i++) {
    for (int j = 0; j < gi->current_figure->width; j++) {
      if (gi->current_figure->matrix[i][j]) {
        temp_field[gi->current_figure->y + i][gi->current_figure->x + j].value =
            1;
        temp_field[gi->current_figure->y + i][gi->current_figure->x + j]
            .color_pair = gi->current_figure->color_pair;
      }
    }
  }
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      attron(COLOR_PAIR(temp_field[i][j].color_pair));
      if (temp_field[i][j].value) {
        printw("%3c", ' '); // рисовать фигуру
      } else {
        printw("%3c", ' '); // пустое пространство
      }
      attroff(COLOR_PAIR(temp_field[i][j].color_pair));
    }
    printw("\n");
  }
  for (int i = 0; i < gi->next_figure->height; i++) {
    for (int j = 0; j < gi->next_figure->width; j++) {
      mvaddch(i + 10, j + 50, gi->next_figure->matrix[i][j] ? '#' : ' ');
    }
  }
  curs_set(120);
  printw("\tscore: %d", gi->score);
  printw("\thigh score: %d", gi->high_score);
  curs_set(0);
  refresh();
}

void move_down(cell_t field[][WIDTH], int line) {
  for (int i = line; i > 0; i--) {
    for (int j = 0; j < WIDTH; j++) {
      field[i][j] = field[i - 1][j];
      usleep(1000);
    }
  }
}

int clear_lines(cell_t field[][WIDTH]) {
  int total_cleared = 0;
  for (int i = 0; i < HEIGHT; i++) {
    int total_filled = 0;
    for (int j = 0; j < WIDTH; j++) {
      total_filled += field[i][j].value;
    }
    if (total_filled == WIDTH) {
      move_down(field, i);
      total_cleared++;
    }
  }
  return total_cleared;
}