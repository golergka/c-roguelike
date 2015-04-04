#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include "input.h"
#include "render.h"
#include "game.h"

static InputState input;
static GameState game;

static pthread_mutex_t input_mutex;
static pthread_mutex_t game_mutex;

const useconds_t input_sleep	= 1000;
const useconds_t game_sleep		= 1000;
const useconds_t render_sleep	= 1000;
const useconds_t main_sleep		= 1000;

static void* input_loop(void* arg)
{
	pthread_mutex_lock(&input_mutex);
	input_init();
	pthread_mutex_unlock(&input_mutex);
	while(true)
	{
		pthread_mutex_lock(&input_mutex);
		input_get(&input);
		pthread_mutex_unlock(&input_mutex);
		usleep(input_sleep);
	}
}

static void* game_loop(void* arg)
{
	pthread_mutex_lock(&game_mutex);
	game_init(&game);
	pthread_mutex_unlock(&game_mutex);
	while(true)
	{
		pthread_mutex_lock(&input_mutex);
		pthread_mutex_lock(&game_mutex);
		game_process_input(&input, &game);
		input_clear(&input);
		pthread_mutex_unlock(&game_mutex);
		pthread_mutex_unlock(&input_mutex);
		usleep(game_sleep);
	}
}

static void* render_loop(void* arg)
{
	render_init();
	while(true)
	{
		pthread_mutex_lock(&game_mutex);
		render(&game);
		pthread_mutex_unlock(&game_mutex);
		usleep(render_sleep);
	}
}

int main(int argc, char** argv)
{
	// Create input mutex
	{
		int input_mutex_error = pthread_mutex_init(&input_mutex, NULL);
		if (input_mutex_error != 0)
		{
			fprintf(
					stderr,
					"Couldn't initialize input mutex, error %d",
					input_mutex_error
				);
		}
	}
	// Create game mutex
	{
		int game_mutex_error = pthread_mutex_init(&game_mutex, NULL);
		if (game_mutex_error != 0)
		{
			fprintf(
					stderr,
					"Couldn't initialize game mutex, error %d",
					game_mutex_error
				);
		}
	}

	// Create and run threads
	pthread_t input_thread;
	{
		int input_thread_error = pthread_create(
				&input_thread,
				NULL,
				&input_loop,
				NULL
			);
		if (input_thread_error != 0)
		{
			fprintf(
					stderr,
					"Couldn't start input thread, error code %d",
					input_thread_error
				);
			return 1;
		}
	}
	pthread_t game_thread;
	{
		int game_thread_error = pthread_create(
				&game_thread,
				NULL,
				&game_loop,
				NULL
			);
		if (game_thread_error != 0)
		{
			fprintf(
					stderr,
					"Couldn't start game thread, error code %d",
					game_thread_error
				);
			return 1;
		}
	}
	pthread_t render_thread;
	{
		int render_thread_error = pthread_create(
				&render_thread,
				NULL,
				&render_loop,
				NULL
			);
		if (render_thread_error != 0)
		{
			fprintf(
					stderr,
					"Couldn't start render thread, error code %d",
					render_thread_error
				);
			return 1;
		}
	}

	// Let the threads run
	while(!input.quit)
	{
		usleep(main_sleep);
	}

	// Quit the game, finish the threads
	return pthread_cancel(input_thread) &
		pthread_cancel(game_thread) &
		pthread_cancel(render_thread);
}

