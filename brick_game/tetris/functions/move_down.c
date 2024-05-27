#include "../tetris.h"
//Сдвигает все строки игрового поля, расположенные выше указанной линии, вниз.
// `line`: Номер строки, с которой начинается сдвиг.
// Цикл `for` проходит по строкам, начиная со строки `line` и заканчивая первой
// строкой
//Внутри цикла:
// Каждая ячейка текущей строки (`i`) копируется в ячейку предыдущей строки (`i
// - 1`).
//Вызывается функция `usleep()` для создания задержки, чтобы анимация выглядела
//плавной.
void move_down(cell_t field[][WIDTH], int line) {
  for (int i = line; i > 0; i--) {
    for (int j = 0; j < WIDTH; j++) {
      field[i][j] = field[i - 1][j];
      usleep(1000);
    }
  }
}
