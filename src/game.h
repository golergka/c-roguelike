#ifndef __GAME_H__
#define __GAME_H__

#include "input.h"

typedef int Coordinate;

typedef struct {
	Coordinate x;
	Coordinate y;
} Position;

typedef enum {
	LEVEL_TILE_UNKNOWN = 0,
	LEVEL_TILE_WALL,
	LEVEL_TILE_FREE
} LevelTile;

#define LEVEL_SIZE 30

typedef struct {
	LevelTile tiles[LEVEL_SIZE][LEVEL_SIZE];
} Level;

typedef struct {
	Position	playerPosition;
	Level		level;
} GameState;

void game_init(GameState* game);

void game_process_input(InputState* input, GameState* game);

#endif
