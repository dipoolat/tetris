#ifndef _TETRIS_H

#define _TETRIS_H

#include "headers/figure.h"
#include "headers/file_reader.h"
#include "types/cell.h"
#include "types/states.h"
#include <ncurses.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define WIDTH 10
#define HEIGHT 20

#define UNUSED(x) ((void)(x))

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

void move_figure(game_info_t *gi);
void recall(game_info_t *gi, pthread_t *thread);
void quick_fall(game_info_t *gi);
void gain_score(game_info_t *gi);
void take_pause(game_info_t *gi);
void terminate_figure(game_info_t *gi, pthread_t **thread);
void init_ncurses();
void rotate_figure(game_info_t *gi);
void render(game_info_t *gi);
void move_figure(game_info_t *gi);
void restore_rotate(game_info_t *gi);
void *fall_figure(void *gi);
void spawn_figure(game_info_t *gi, pthread_t **thread);
void move_down(cell_t field[][WIDTH], int line);

int game_over(game_info_t *gi);
int calculate_score(int lines_cleared);
int is_collision_y(game_info_t *gi);
int is_collision_x(game_info_t *gi, int dir);
int clear_lines(cell_t field[][WIDTH]);

void render(game_info_t *gi);
void render_border();
void render_game(cell_t t[HEIGHT][WIDTH]);
void render_next_figure(game_info_t *gi);
void render_side_panel(game_info_t *gi);
void terminate_game(game_info_t *gi);

void copy_array(cell_t ar[][WIDTH], cell_t t[][WIDTH]);
void sum_array(game_info_t *gi, cell_t t[][WIDTH]);

game_state_t get_current_state();

#endif //_TETRIS_H