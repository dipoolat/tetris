all: build run


create_obj_dir:
	@mkdir obj -p


compile: create_obj_dir
	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/functions/calc_score.c -lncurses -o obj/calc_score.o
	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/functions/clear_lines.c -lncurses -o obj/clear_lines.o
	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/functions/fall_figure.c -lncurses -o obj/fall_figure.o
	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/functions/gain_score.c -lncurses -o obj/gain_score.o
	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/functions/game_over.c -lncurses -o obj/game_over.o
	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/functions/get_current_state.c -lncurses -o obj/get_current_state.o
	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/functions/init_ncurses.c -lncurses -o obj/init_ncurses.o
	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/functions/is_collision_x.c -lncurses -o obj/is_collision_x.o
	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/functions/is_collision_y.c -lncurses -o obj/is_collision_y.o
	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/functions/move_down.c -lncurses -o obj/move_down.o
	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/functions/move_figure.c -lncurses -o obj/move_figure.o
	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/functions/quick_fall.c -lncurses -o obj/quick_fall.o
	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/functions/recall.c -lncurses -o obj/recall.o
	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/functions/restore_rotate.c -lncurses -o obj/restore_rotate.o
	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/functions/rotate.c -lncurses -o obj/rotate.o
	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/functions/spawn_figure.c -lncurses -o obj/spawn_figure.o
	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/functions/take_pause.c -lncurses -o obj/take_pause.o
	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/functions/terminate_figure.c -lncurses -o obj/terminate_figure.o

	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/figure.c -lncurses -o obj/figure.o
	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/file_reader.c -lncurses -o obj/file_reader.o

	@gcc -g -Wall -Wextra -Werror -c gui/cli/components/border.c -lncurses -o obj/border.o
	@gcc -g -Wall -Wextra -Werror -c gui/cli/components/game_over.c -lncurses -o obj/terminate_game.o
	@gcc -g -Wall -Wextra -Werror -c gui/cli/components/game.c -lncurses -o obj/game.o
	@gcc -g -Wall -Wextra -Werror -c gui/cli/components/next_figure.c -lncurses -o obj/next_figure.o
	@gcc -g -Wall -Wextra -Werror -c gui/cli/components/side_panel.c -lncurses -o obj/side_panel.o

	@gcc -g -Wall -Wextra -Werror -c gui/cli/copy_array.c -lncurses -o obj/copy_array.o
	@gcc -g -Wall -Wextra -Werror -c gui/cli/render.c -lncurses -o obj/render.o
	@gcc -g -Wall -Wextra -Werror -c gui/cli/sum_array.c -lncurses -o obj/sum_array.o

	@ar rcs tetris_core.a obj/*
	@ranlib tetris_core.a


compile_gcov: clean create_obj_dir
	@gcc --coverage -g -Wall -Wextra -Werror -c brick_game/tetris/functions/calc_score.c -lncurses -o obj/calc_score.o
	@gcc --coverage -g -Wall -Wextra -Werror -c brick_game/tetris/functions/clear_lines.c -lncurses -o obj/clear_lines.o
	@gcc --coverage -g -Wall -Wextra -Werror -c brick_game/tetris/functions/fall_figure.c -lncurses -o obj/fall_figure.o
	@gcc --coverage -g -Wall -Wextra -Werror -c brick_game/tetris/functions/gain_score.c -lncurses -o obj/gain_score.o
	@gcc --coverage -g -Wall -Wextra -Werror -c brick_game/tetris/functions/game_over.c -lncurses -o obj/game_over.o
	@gcc --coverage -g -Wall -Wextra -Werror -c brick_game/tetris/functions/get_current_state.c -lncurses -o obj/get_current_state.o
	@gcc --coverage -g -Wall -Wextra -Werror -c brick_game/tetris/functions/init_ncurses.c -lncurses -o obj/init_ncurses.o
	@gcc --coverage -g -Wall -Wextra -Werror -c brick_game/tetris/functions/is_collision_x.c -lncurses -o obj/is_collision_x.o
	@gcc --coverage -g -Wall -Wextra -Werror -c brick_game/tetris/functions/is_collision_y.c -lncurses -o obj/is_collision_y.o
	@gcc --coverage -g -Wall -Wextra -Werror -c brick_game/tetris/functions/move_down.c -lncurses -o obj/move_down.o
	@gcc --coverage -g -Wall -Wextra -Werror -c brick_game/tetris/functions/move_figure.c -lncurses -o obj/move_figure.o
	@gcc --coverage -g -Wall -Wextra -Werror -c brick_game/tetris/functions/quick_fall.c -lncurses -o obj/quick_fall.o
	@gcc --coverage -g -Wall -Wextra -Werror -c brick_game/tetris/functions/recall.c -lncurses -o obj/recall.o
	@gcc --coverage -g -Wall -Wextra -Werror -c brick_game/tetris/functions/restore_rotate.c -lncurses -o obj/restore_rotate.o
	@gcc --coverage -g -Wall -Wextra -Werror -c brick_game/tetris/functions/rotate.c -lncurses -o obj/rotate.o
	@gcc --coverage -g -Wall -Wextra -Werror -c brick_game/tetris/functions/spawn_figure.c -lncurses -o obj/spawn_figure.o
	@gcc --coverage -g -Wall -Wextra -Werror -c brick_game/tetris/functions/take_pause.c -lncurses -o obj/take_pause.o
	@gcc --coverage -g -Wall -Wextra -Werror -c brick_game/tetris/functions/terminate_figure.c -lncurses -o obj/terminate_figure.o

	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/figure.c -lncurses -o obj/figure.o
	@gcc -g -Wall -Wextra -Werror -c brick_game/tetris/file_reader.c -lncurses -o obj/file_reader.o

	@gcc -g -Wall -Wextra -Werror -c gui/cli/components/border.c -lncurses -o obj/border.o
	@gcc -g -Wall -Wextra -Werror -c gui/cli/components/game_over.c -lncurses -o obj/terminate_game.o
	@gcc -g -Wall -Wextra -Werror -c gui/cli/components/game.c -lncurses -o obj/game.o
	@gcc -g -Wall -Wextra -Werror -c gui/cli/components/next_figure.c -lncurses -o obj/next_figure.o
	@gcc -g -Wall -Wextra -Werror -c gui/cli/components/side_panel.c -lncurses -o obj/side_panel.o

	@gcc --coverage -g -Wall -Wextra -Werror -c gui/cli/copy_array.c -lncurses -o obj/copy_array.o
	@gcc -g -Wall -Wextra -Werror -c gui/cli/render.c -lncurses -o obj/render.o
	@gcc --coverage -g -Wall -Wextra -Werror -c gui/cli/sum_array.c -lncurses -o obj/sum_array.o

	@ar rcs tetris_core.a obj/*
	@ranlib tetris_core.a



build: compile
	@gcc -Wall -Wextra -Werror brick_game/tetris/main.c tetris_core.a -lncurses -o tetris


run: build
	@./tetris


clean:
	@rm -rf docs obj tetris high_score report.out *.dSYM *.a *.out *.gcov *.info *.gcda *.gcno *.o out report test.out


style:
	@clang-format -i *.c *.h */*.c */*.h */*/*.c */*/*.h */*/*/*.c */*/*/*.h


test: compile
	@gcc -Wall -Wextra -Werror test/tetris_test.c tetris_core.a -o test.out -lcheck -lm -lpthread -lrt -lsubunit -lncurses
	@./test.out


gcov_report: compile_gcov
	@gcc -c -Wall -Wextra -Werror test/tetris_test.c -o obj/tetris_test.o
	@gcc -fprofile-arcs -ftest-coverage obj/tetris_test.o  tetris_core.a -lcheck -lsubunit -lm -lncurses -o test.out
	@./test.out
	@lcov --capture --directory . --output-file coverage.info
	@genhtml coverage.info --output-directory out


dvi:
	@doxygen