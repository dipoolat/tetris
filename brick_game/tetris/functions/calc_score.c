#include "../tetris.h"
// в функцию на вход подается количество очищенных линий, 
//в зависимости от этого начисляются очки
int calculate_score(int lines_cleared) {
  switch (lines_cleared) {
  case 1:
    return 100;
  case 2:
    return 300;
  case 3:
    return 700;
  case 4:
    return 1500;
  default:
    return 0;
  }
}
