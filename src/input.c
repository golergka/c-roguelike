#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>
#include <curses.h>
#include "input.h"

void input_init()
{
	static struct termios term_props;
	tcgetattr(STDIN_FILENO, &term_props);
	term_props.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &term_props);
}

void input_get(InputState* input)
{
	struct timeval tv;
	fd_set fs;
	tv.tv_usec = tv.tv_sec = 0;
	FD_ZERO(&fs);
	FD_SET(STDIN_FILENO, &fs);
	select(STDIN_FILENO + 1, &fs, 0, 0, &tv);

	int c = 0;
	if (FD_ISSET(STDIN_FILENO, &fs))
	{
		c = getchar();
	}
	input->quit = (c == 'q');

	if (c == 'w')
	{
		input->moveDirection = DIRECTION_UP;
	}
	else if (c == 's')
	{
		input->moveDirection = DIRECTION_DOWN;
	}
	else if (c == 'a')
	{
		input->moveDirection = DIRECTION_LEFT;
	}
	else if (c == 'd')
	{
		input->moveDirection = DIRECTION_RIGHT;
	}
	else
	{
		input->moveDirection = DIRECTION_NONE;
	}
}

