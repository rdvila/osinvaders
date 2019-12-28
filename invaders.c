#include "invaders.h"

#include <stdlib.h>

#include "timer.h"
#include "sprites.h"
#include "graphics.h"
#include "sound.h"
#include "screen.h"

int invaders_init(void)
{
	atexit(invaders_quit);

	timer_init_default();
	sprites_init(screen_mode);
	graphics_init();
	sound_init();
	screen_init();

	return 0;
}

void invaders_quit(void)
{
	sound_quit();
	SDL_Quit();
}

int invaders_loop(void)
{
	return screen_loop();		
}
