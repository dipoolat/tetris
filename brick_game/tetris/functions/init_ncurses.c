#include "../tetris.h"
//функция инициализирует библиотеку ncurses для вывода графики в консоли.

//Вызывается функция `initscr()`, чтобы инициализировать экран ncurses.
//Включаются различные опции ncurses:
// `noecho()`: отключает отображение введенных символов на экране.
//`cbreak()`: включает режим "немедленного ввода", т. е. ввод обрабатывается сразу после нажатия клавиши.
// `keypad(stdscr, TRUE)`: включает обработку функциональных клавиш.
//`curs_set(0)`: скрывает курсор.
//`timeout(100)`: устанавливает таймаут для ввода в 100 миллисекунд.
//- Вызывается функция `start_color()`, чтобы включить поддержку цвета.
//- Задаются цветовые пары для разных элементов игры.
void init_ncurses() {
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(0);
  timeout(100);
  start_color();
  init_pair(0, COLOR_BLACK, COLOR_BLACK);
  init_pair(1, COLOR_BLACK, COLOR_BLUE);
  init_pair(2, COLOR_BLACK, COLOR_CYAN);
  init_pair(3, COLOR_BLACK, COLOR_GREEN);
  init_pair(4, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(5, COLOR_BLACK, COLOR_RED);
  init_pair(6, COLOR_BLACK, COLOR_YELLOW);
  init_pair(7, COLOR_BLACK, COLOR_WHITE);
  init_pair(8, COLOR_RED, COLOR_BLACK);
}