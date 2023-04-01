#include <termios.h>
#include <stdio.h>
#include "interface.h"

extern char cmd_cursup[];
extern char cmd_cursdw[];
extern char cmd_cursfw[];
extern char cmd_cursbk[];

#define ValToChar(x) x+48
#define StepOffset 2

#define SetStep(cmd, step) cmd[StepOffset] = ValToChar(step)

int setterminal(void);

int gameinit(void)
{
	SetStep(cmd_cursup, 1);
	SetStep(cmd_cursdw, 1);
	SetStep(cmd_cursfw, 1);
	SetStep(cmd_cursbk, 1);

	setterminal();

	return 0;
}

int setterminal(void)
{

	struct termios tcinfo;

	if(tcgetattr(0, &tcinfo) == -1)
	{
		perror("[ERROR]tcgetattr");
		return -1;
	}

	tcinfo.c_lflag &= ~ECHO;
	tcinfo.c_lflag &= ~ICANON;

	if(tcsetattr(0, TCSANOW, &tcinfo) == -1)
	{
		perror("[ERROR]tcsetattr");
		return -1;
	}

	return 0;
}
