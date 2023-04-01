#include "game.h"

int main(int argv, char *argc[])
{
	char key;

	gameinit();
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
