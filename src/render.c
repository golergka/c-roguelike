#include <curses.h>
#include <string.h>
#include "render.h"

void render_init()
{
	initscr();
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
}

void render()
{
	erase();
	int row,col;
	getmaxyx(stdscr,row,col);
	char mesg[] = "Render screen";
	mvprintw(row/2,(col-strlen(mesg))/2, "%s", mesg);
	mvprintw(row-1,0,"%d rows %d columns\n", row,col);
	refresh();
}
