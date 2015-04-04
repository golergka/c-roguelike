#ifndef __GAME_H__
#define __GAME_H__

#include "input.h"

typedef int Coordinate;

typedef struct {
	Coordinate x;
	Coordinate y;
} Position;

typedef struct {
	Position playerPosition;
} GameState;

void game_process_input(InputState* input, GameState* game);

#endif
