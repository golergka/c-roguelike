#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "render.h"

void clear_screen()
{
	rewind(stdout);
	printf("\033[2J\033[1;1H");
}

void render_line(int c, int length)
{
	for(int x = 0; x < length; x++)
	{
		putchar(c);
	}
}

void render()
{
	clear_screen();

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	render_line('+', w.ws_col);
	for(int y = 1; y < w.ws_row - 1; y++)
	{
		putchar('+');
		render_line(' ', w.ws_col - 2);
		putchar('+');
	}
	render_line('+', w.ws_col);
	usleep(1);
}
