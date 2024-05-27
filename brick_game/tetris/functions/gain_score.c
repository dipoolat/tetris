#include "../tetris.h"
//Эта функция обновляет счет игры после завершения падения фигуры
//К счету игры (`gi->score`) добавляется количество очков, соответствующее
//количеству очищенных линий
// Если текущий счет больше максимального счета, максимальный счет обновляется.
void gain_score(game_info_t *gi) {
  gi->score += calculate_score(clear_lines(gi->game_field));
  if (gi->score > gi->high_score)
    set_high_score(gi->score);
  gi->level = gi->score / 600 + 1;
  if (gi->level > 10)
    gi->level = 10;
}