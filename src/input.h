#ifndef __INPUT_H__
#define __INPUT_H__

#include <stdbool.h>

typedef enum {
	DIRECTION_NONE = 0,
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT
} Direction;

typedef struct {
	bool		quit;
	Direction	move_direction;
} InputState;

void input_init();

void input_get(InputState* input);

void input_clear(InputState* input);

bool input_is_dirty(InputState* input);

#endif // __INPUT_H__
