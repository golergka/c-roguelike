#include <stdio.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>

typedef struct {
	bool quit;
} InputState;

void input_init()
{
	static struct termios term_props;
	tcgetattr(STDIN_FILENO, &term_props);
	term_props.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &term_props);
}

void input_get(InputState* input)
{
	struct timeval tv;
	fd_set fs;
	tv.tv_usec = tv.tv_sec = 0;
	FD_ZERO(&fs);
	FD_SET(STDIN_FILENO, &fs);
	select(STDIN_FILENO + 1, &fs, 0, 0, &tv);

	int c = 0;
	if (FD_ISSET(STDIN_FILENO, &fs))
	{
		c = getchar();
	}
	input->quit = (c == 'q');
}

void render()
{
	rewind(stdout);
	printf("\033[2J\033[1;1H");
	puts("Render frame");
	usleep(100);
}

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
