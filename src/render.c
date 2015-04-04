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

char char_for_tile(LevelTile tile)
{
	switch(tile)
	{
		case(LEVEL_TILE_FREE):
			return '.';
		case(LEVEL_TILE_WALL):
			return '#';
		case(LEVEL_TILE_UNKNOWN):
			return ' ';
		default:
			return '?';
	}
}

LevelTile get_tile(GameState* game, int x, int y)
{
	if (x >= 0 && x < LEVEL_SIZE && y >= 0 && y < LEVEL_SIZE)
	{
		return game->level.tiles[x][y];
	}
	else
	{
		return LEVEL_TILE_UNKNOWN;
	}
}

void render(GameState* game)
{
	erase();
	int row,col;
	getmaxyx(stdscr,row,col);
	// Player position in the first row
	mvprintw(
			0,
			0,
			"Player position: x=%d y=%d", 
			game->playerPosition.x,
			game->playerPosition.y
		);
	for(int y = 1; y < row - 1; y++)
	{
		for(int x = 0; x < col; x++)
		{
			mvaddch(y, x, char_for_tile(get_tile(game,x,y)));
		}
	}

	mvaddch(
			game->playerPosition.y,
			game->playerPosition.x,
			'@'
		);
	// Screen size in the last row
	mvprintw(
			row-1,
			0,
			"%d rows %d columns\n", 
			row, 
			col
		);
	refresh();
}
