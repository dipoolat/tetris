#include "../../../brick_game/tetris/tetris.h"
//Отображает сообщение о завершении игры на экране.
void terminate_game(game_info_t *gi) {
  int y, x;
  getmaxyx(stdscr, y, x);
  mvprintw(y / 2, x / 2 - strlen("Game Over") / 2, "Game Over");
  mvprintw(y / 2 + 2, x / 2 - strlen("You got 00000 points") / 2,
           "You got %05d points", gi->score);
  mvprintw(y / 2 + 4, x / 2 - strlen("Press any key to proceed") / 2,
           "Press any key to proceed");
  timeout(-1);
  getch();
}
