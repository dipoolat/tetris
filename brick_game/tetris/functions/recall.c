#include "../tetris.h"
//очищает ресурсы, связанные с текущей игрой, прежде чем завершить ее
//Закрывает ncurses.
//Удаляет текущую и следующую фигуры из памяти.
//Завершает работу потока, отвечающего за падение фигуры.
//Освобождает память, выделенную для указателя на поток.
void recall(game_info_t *gi, pthread_t *thread) {
  endwin();

  if (gi->current_figure)
    delete_figure(gi->current_figure);
  if (gi->next_figure)
    delete_figure(gi->next_figure);
  if (thread) {
    pthread_cancel(*thread);
    free(thread);
  }
}
