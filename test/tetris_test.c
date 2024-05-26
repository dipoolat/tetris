#include "../brick_game/tetris/tetris.h"
#include <check.h>

START_TEST(calc_score) {
  ck_assert_int_eq(100, calculate_score(1));
  ck_assert_int_eq(300, calculate_score(2));
  ck_assert_int_eq(700, calculate_score(3));
  ck_assert_int_eq(1500, calculate_score(4));
  ck_assert_int_eq(0, calculate_score(5));
  ck_assert_int_eq(0, calculate_score(-1));
}
END_TEST

Suite *tetris_suite(void) {
  Suite *suite = suite_create("tetris");
  TCase *tcase_core = tcase_create("core");

  tcase_add_test(tcase_core, calc_score);

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
