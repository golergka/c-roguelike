#include <stdio.h>
#include <unistd.h>
#include "render.h"

void render()
{
	rewind(stdout);
	printf("\033[2J\033[1;1H");
	puts("Render frame");
	usleep(100);
}
