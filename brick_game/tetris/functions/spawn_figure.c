#include "../tetris.h"
//Создает новую фигуру и запускает ее падение в отдельном потоке.
//Если `gi->next_figure` равно NULL, создается новая фигура (`gi->next_figure`).
//Текущая фигура (`gi->current_figure`) становится равной следующей фигуре
//(`gi->next_figure`). Создается новая фигура для `gi->next_figure`. Создается
//новый поток с помощью `pthread_create`, в котором запускается функция
//`fall_figure`.
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
  if (*thread != NULL)
    free(*thread);
  *thread = calloc(1, sizeof(pthread_t));
  pthread_create(*thread, NULL, fall_figure, gi);
}