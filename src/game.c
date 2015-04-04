#include "game.h"

void game_process_input(InputState* input, GameState* game)
{
	switch(input->moveDirection)
	{
		case(DIRECTION_DOWN):
			game->playerPosition.y--;
			break;
		case(DIRECTION_UP):
			game->playerPosition.y++;
			break;
		case(DIRECTION_LEFT):
			game->playerPosition.x--;
			break;
		case(DIRECTION_RIGHT):
			game->playerPosition.x++;
			break;
		case(DIRECTION_NONE):
			break;
		default:
			// TODO error throwing
			break;
	}
}
