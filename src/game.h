#ifndef __GAME_H__
#define __GAME_H__

#include <stdbool.h>
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
	Position	position;
	int			hit_points;
	bool		spawned;
} Enemy;

typedef struct {
	Position	position;
	int			hit_points_current;
	int			hit_points_max;
} Player;

#define GAME_ENEMIES 10

typedef struct {
	Player		player;
	Enemy		enemies[GAME_ENEMIES];
	Level		level;
} GameState;

void game_init(GameState* game);

void game_process_input(InputState* input, GameState* game);

#endif
