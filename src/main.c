#include <unistd.h>
#include "input.h"
#include "render.h"

int main(int argc, char** argv)
{
	render_init();
	input_init();
	InputState input;
	while(!input.quit)
	{
		input_get(&input);
		render();
	}
	return 0;
}
