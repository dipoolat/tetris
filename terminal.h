#ifndef _TERMINAL_H

#define _TERMINAL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

void enter_conon(void);
void exit_conon(void);

#endif // _TERMINAL_H