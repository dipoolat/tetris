#include "../brick_game/tetris/tetris.h"
#include <check.h>

START_TEST(calc_score_t) {
  ck_assert_int_eq(100, calculate_score(1));
  ck_assert_int_eq(300, calculate_score(2));
  ck_assert_int_eq(700, calculate_score(3));
  ck_assert_int_eq(1500, calculate_score(4));
  ck_assert_int_eq(0, calculate_score(5));
  ck_assert_int_eq(0, calculate_score(-1));
}
END_TEST

START_TEST(take_pause_t) {
  game_info_t gi = {0};
  gi.state = PAUSE;
  take_pause(&gi);
  ck_assert_int_eq(1, gi.pause);
  take_pause(&gi);
  ck_assert_int_eq(0, gi.pause);
  gi.state = DOWN;
  take_pause(&gi);
  ck_assert_int_eq(0, gi.pause);
}
END_TEST

START_TEST(quick_fall_t) {
  game_info_t gi = {0};
  gi.state = FAST_DOWN;
  gi.current_figure = calloc(1, sizeof(figure_t));
  create_figure_matrix(gi.current_figure);
  quick_fall(&gi);
  gi.state = DOWN;
  quick_fall(&gi);
  if (gi.current_figure->height == 2)
    ck_assert_int_eq(HEIGHT - 2, gi.current_figure->y);
  else 
    ck_assert_int_eq(HEIGHT - 1, gi.current_figure->y);
}
END_TEST

START_TEST(is_collision_x_t) {
  game_info_t gi = {0};
  gi.current_figure = calloc(1, sizeof(figure_t));
  create_figure_matrix(gi.current_figure);
  ck_assert_int_eq(0, is_collision_x(&gi, -1));
  ck_assert_int_eq(0, is_collision_x(&gi, 1));
  gi.game_field[0][gi.current_figure->width].value = 1;
  gi.game_field[1][gi.current_figure->width].value = 1;
  ck_assert_int_eq(1, is_collision_x(&gi, 1));
  delete_figure(gi.current_figure);
}
END_TEST

START_TEST(gain_score_t) {
  game_info_t gi1 = {0};
  game_info_t gi2 = {0};
  game_info_t gi3 = {0};
  game_info_t gi4 = {0};
  game_info_t gi5 = {0};
  for (int i = 0; i < WIDTH; i++) {
    gi1.game_field[0][i].value = 1;
    gi2.game_field[0][i].value = 1;
    gi2.game_field[1][i].value = 1;
    gi3.game_field[0][i].value = 1;
    gi3.game_field[1][i].value = 1;
    gi3.game_field[2][i].value = 1;
    gi4.game_field[0][i].value = 1;
    gi4.game_field[1][i].value = 1;
    gi4.game_field[2][i].value = 1;
    gi4.game_field[3][i].value = 1;

  }
  gain_score(&gi1);
  gain_score(&gi2);
  gain_score(&gi3);
  gain_score(&gi4);
  gain_score(&gi5);
  ck_assert_int_eq(100, gi1.score);
  ck_assert_int_eq(300, gi2.score);
  ck_assert_int_eq(700, gi3.score);
  ck_assert_int_eq(1500, gi4.score);
  ck_assert_int_eq(0, gi5.score);
}
END_TEST

START_TEST(gm_over_t) {
  game_info_t gi = {0};
  game_info_t gi1 = {0};
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      gi1.game_field[i][j].value = 1;
    }
  }
  gi.current_figure = calloc(1, sizeof(figure_t));
  gi1.current_figure = calloc(1, sizeof(figure_t));
  create_figure_matrix(gi.current_figure);
  create_figure_matrix(gi1.current_figure);
  ck_assert_int_eq(0, game_over(&gi));
  ck_assert_int_eq(1, game_over(&gi1));
  delete_figure(gi.current_figure);
  delete_figure(gi1.current_figure);
}
END_TEST

START_TEST(clear_lines_t) {
  cell_t arr1[HEIGHT][WIDTH] = {0};
  cell_t arr2[HEIGHT][WIDTH] = {0};
  cell_t arr3[HEIGHT][WIDTH] = {0};
  cell_t arr4[HEIGHT][WIDTH] = {0};
  cell_t arr5[HEIGHT][WIDTH] = {0};
  for (int i = 0; i < WIDTH; i++) {
    arr1[0][i].value = 1;
    arr2[0][i].value = 1;
    arr2[1][i].value = 1;
    arr3[0][i].value = 1;
    arr3[1][i].value = 1;
    arr3[2][i].value = 1;
    arr4[0][i].value = 1;
    arr4[1][i].value = 1;
    arr4[2][i].value = 1;
    arr4[3][i].value = 1;

  }
  ck_assert_int_eq(1, clear_lines(arr1));
  ck_assert_int_eq(2, clear_lines(arr2));
  ck_assert_int_eq(3, clear_lines(arr3));
  ck_assert_int_eq(4, clear_lines(arr4));
  ck_assert_int_eq(0, clear_lines(arr5));
}
END_TEST


Suite *tetris_suite(void) {
  Suite *suite = suite_create("tetris");
  TCase *tcase_core = tcase_create("core");

  tcase_add_test(tcase_core, calc_score_t);
  tcase_add_test(tcase_core, gm_over_t);
  tcase_add_test(tcase_core, clear_lines_t);
  tcase_add_test(tcase_core, gain_score_t);
  tcase_add_test(tcase_core, is_collision_x_t);
  tcase_add_test(tcase_core, quick_fall_t);
  tcase_add_test(tcase_core, take_pause_t);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

int main(void) {
  Suite *suite = tetris_suite();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_VERBOSE);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return (failed_count == 0) ? 0 : 1;
}
