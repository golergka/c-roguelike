#include <stdbool.h>
#include "input.h"
#include "render.h"

int main(int argc, char** argv)
{
	input_init();
	InputState input;
	while(!input.quit)
	{
		input_get(&input);
		render();
	}
	return 0;
}
