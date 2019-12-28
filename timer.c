#include "timer.h"

#include "settings.h"

void timer_init_default()
{
	start_ticks = 0;
	pause_ticks = 0;
}

void timer_start(void)
{
	started = SDL_TRUE;
	paused  = SDL_FALSE;

	start_ticks = SDL_GetTicks();
	pause_ticks = 0;
}

void timer_stop(void)
{
	started = SDL_FALSE;
	paused  = SDL_TRUE;
}

void timer_pause(void)
{
	if (started && !paused) {
		paused = SDL_TRUE;
		pause_ticks = (SDL_GetTicks() - start_ticks);
	}
}

void timer_unpause(void)
{
	if (paused) {
		paused = SDL_FALSE;
		start_ticks = (SDL_GetTicks() - pause_ticks);
		pause_ticks = 0;
	}
}

Uint32 timer_get_ticks(void)
{
	if (started) {
		if (paused) {
			return pause_ticks;
		}
		else {
			return (SDL_GetTicks() - start_ticks);
		}
	}

	return 0;
}

void timer_delay(void)
{
	Uint32 ticks = timer_get_ticks();

	#ifdef GAME_DEBUG
		printf("STOP: %u\n", ticks);
	#endif

	if (ticks < (1000.0f / screen_fps)) {
		SDL_Delay((1000.0f/ screen_fps) - ticks);
	}
}
