#ifndef __INPUT_H__
#define __INPUT_H__

typedef struct {
	bool quit;
} InputState;

void input_init();

void input_get(InputState* input);

#endif // __INPUT_H__
