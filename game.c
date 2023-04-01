#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>

#define ANSI_LEN 4

#define ValToChar(x) x+48
#define StepOffset 2

#define CursorUp "\x1B[ A"
#define CursorDown "\x1B[ B"
#define CursorForward "\x1B[ D"
#define CursorBack "\x1B[ C"

#define SetStep(cmd, step) cmd[StepOffset] = ValToChar(step)

char cmd_cursup[] = CursorUp;
char cmd_cursdw[] = CursorDown;
char cmd_cursfw[] = CursorForward;
char cmd_cursbk[] = CursorBack;

int main(int argv, char *argc[])
{
	char key;
	int setterminal(void);

	SetStep(cmd_cursup, 9);
	SetStep(cmd_cursdw, 9);
	SetStep(cmd_cursfw, 1);
	SetStep(cmd_cursbk, 1);

//	write(1, " i", 2);
//	write(1, cmd, strlen(cmd));
//	write(1, "h\n", 3);

	setterminal();
	while(1)
	{
		read(0, &key, 1);
		if(key == 'a') write(1, cmd_cursfw, strlen(cmd_cursfw));
		if(key == 'd') write(1, cmd_cursbk, strlen(cmd_cursbk));
		if(key == 'w') write(1, cmd_cursup, strlen(cmd_cursup));
		if(key == 's') write(1, cmd_cursdw, strlen(cmd_cursdw));

		fflush(0);
	}
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
