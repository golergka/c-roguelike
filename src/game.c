#include <stdlib.h>
#include "game.h"

void game_init(GameState* game)
{
	// Generate level
	game->player.position.x = LEVEL_SIZE/2;
	game->player.position.y = LEVEL_SIZE/2;
	int room_size = 10;
	for(size_t y = 0; y < LEVEL_SIZE; y++)
	{
		for(size_t x = 0; x < LEVEL_SIZE; x++)
		{
			int distance_x = abs(game->player.position.x - x);
			int distance_y = abs(game->player.position.y - y);

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

	// Generate enemies
	int enemies_spawn = 3;
	for(size_t i = 0; i < enemies_spawn; i++)
	{
		game->enemies[i].position.x = game->player.position.x - room_size + 1 + (rand() % (room_size * 2 - 1));
		game->enemies[i].position.y = game->player.position.y - room_size + 1 + (rand() % (room_size * 2 - 1));
		game->enemies[i].spawned = true;
		game->enemies[i].hit_points = 3;
	}

	for(size_t i = enemies_spawn; i < GAME_ENEMIES; i++)
	{
		game->enemies[i].spawned = false;
	}
}

bool are_equal(Position* pos1, Position* pos2)
{
	return pos1->x == pos2->x
		&& pos1->y == pos2->y;
}

Enemy* try_get_enemy(GameState* game, Position* pos)
{
	for(size_t i = 0; i < GAME_ENEMIES; i++)
	{
		if(are_equal(pos, &game->enemies[i].position))
		{
			return &game->enemies[i];
		}
	}
	return NULL;
}

bool can_pass_position(GameState* game, Position* pos)
{
	Enemy* enemy = try_get_enemy(game, pos);
	if (enemy == NULL)
	{
		return !are_equal(&game->player.position, pos)
			&& game->level.tiles[pos->x][pos->y] == LEVEL_TILE_FREE;
	}
	else
	{
		return enemy->hit_points <= 0;
	}
}

void damage_enemy(Enemy* enemy, int damage)
{
	if (enemy->hit_points > damage)
	{
		enemy->hit_points -= damage;
	}
	else
	{
		enemy->hit_points = 0;
	}
}

void game_process_input(InputState* input, GameState* game)
{
	// Move player
	{
		Position new_position = game->player.position;
		switch(input->move_direction)
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

		Enemy* target;
		if (can_pass_position(game, &new_position))
		{
			game->player.position = new_position;
		}
		else if ((target = try_get_enemy(game, &new_position)) != NULL)
		{
			damage_enemy(target, 1);
		}
	}
	// Move enemies
	{
		for(size_t i = 0; i < GAME_ENEMIES; i++)
		{
			Enemy* current = &game->enemies[i];

			if (current->spawned &&
				current->hit_points > 0)
			{
				Position new_position = current->position;
				new_position.x += rand() % 3 - 1;
				new_position.y += rand() % 3 - 1;
				if (can_pass_position(game, &new_position))
				{
					current->position = new_position;
				}
			}
		}
	}
}
