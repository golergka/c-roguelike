#include <unistd.h>
#include "input.h"
#include "render.h"
#include "game.h"

static InputState input;
static GameState game;

int main(int argc, char** argv)
{
	render_init();
	input_init();
	while(!input.quit)
	{
		input_get(&input);
		game_process_input(&input, &game);
		render(&game);
	}
	return 0;
}
