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
			game->player.position.x,
			game->player.position.y
		);

	// Render level
	for(int y = 1; y < row - 1; y++)
	{
		for(int x = 0; x < col; x++)
		{
			mvaddch(y, x, char_for_tile(get_tile(game,x,y)));
		}
	}

	// Render enemies
	for(size_t i = 0; i < GAME_ENEMIES; i++)
	{
		if (game->enemies[i].spawned)
		{
			mvaddch(
					game->enemies[i].position.y,
					game->enemies[i].position.x,
					game->enemies[i].hit_points > 0 ?
						'$' : 
						'^'
				);
		}
	}

	// Render player
	mvaddch(
			game->player.position.y,
			game->player.position.x,
			'@'
		);

	// Status bar
	mvprintw(
			row-1,
			0,
			"HP: %d/%d",
			game->player.hit_points_current,
			game->player.hit_points_max
		);
	refresh();
}
