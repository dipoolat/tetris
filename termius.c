#include "terminal.h"

static struct termios storedSettings;

void enter_conon() {
  struct termios newSettings;
  tcgetattr(0, &storedSettings);
  newSettings = storedSettings;

  newSettings.c_lflag &= (~ICANON);
  newSettings.c_lflag &= (~ECHO);
  newSettings.c_cc[VTIME] = 0;
  newSettings.c_cc[VMIN] = 1;

  tcsetattr(0, TCSANOW, &newSettings);
}

void exit_conon() { tcsetattr(0, TCSANOW, &storedSettings); }
