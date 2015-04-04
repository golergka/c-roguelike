#include <stdbool.h>
#include <stdlib.h>
#include "game.h"

void game_init(GameState* game)
{
	game->playerPosition.x = LEVEL_SIZE/2;
	game->playerPosition.y = LEVEL_SIZE/2;
	int room_size = 10;
	for(size_t y = 0; y < LEVEL_SIZE; y++)
	{
		for(size_t x = 0; x < LEVEL_SIZE; x++)
		{
			int distance_x = abs(game->playerPosition.x - x);
			int distance_y = abs(game->playerPosition.y - y);

			bool inside_x = distance_x < room_size;
			bool inside_y = distance_y < room_size;
			bool inside = inside_x && inside_y;

			bool outside_x = distance_x > room_size;
			bool outside_y = distance_y > room_size;
			bool outside = outside_x || outside_y;

			if (inside)
			{
				game->level.tiles[x][y] = LEVEL_TILE_FREE;
			}
			else if (outside)
			{
				game->level.tiles[x][y] = LEVEL_TILE_UNKNOWN;
			}
			else
			{
				game->level.tiles[x][y] = LEVEL_TILE_WALL;
			}
		}
	}
}

bool can_pass_position(GameState* game, Position pos)
{
	return game->level.tiles[pos.x][pos.y] == LEVEL_TILE_FREE;
}

void game_process_input(InputState* input, GameState* game)
{
	Position new_position = game->playerPosition;
	switch(input->moveDirection)
	{
		case(DIRECTION_DOWN):
			new_position.y++;
			break;
		case(DIRECTION_UP):
			new_position.y--;
			break;
		case(DIRECTION_LEFT):
			new_position.x--;
			break;
		case(DIRECTION_RIGHT):
			new_position.x++;
			break;
		case(DIRECTION_NONE):
			break;
		default:
			// TODO error throwing
			break;
	}
	if (can_pass_position(game, new_position))
	{
		game->playerPosition = new_position;
	}
}
