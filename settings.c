#include "settings.h"

void settings_init_default(void)
{
	screen_mode   = 1;
	screen_width  = 160;
	screen_height = 144;
	screen_bpp    = 32;
	screen_fps    = 20;

	Uint32 flags = SDL_HWSURFACE | SDL_PREALLOC | SDL_HWACCEL;

	screen_flags  = flags;

	fullscreen   = SDL_FALSE;
	enable_sound = SDL_TRUE; 
}

void settings_set_mode(unsigned mode)
{
	screen_mode = mode;

	switch (mode) {
	case 1:
		screen_width  = 160;
		screen_height = 144;
		break;
	case 2:
		screen_width  = 320;
		screen_height = 288;
		break;
	case 3:
		screen_width  = 640;
		screen_height = 576;
		break;

	default:
		fprintf(stderr, "Unknown video mode.\n");
		exit(EXIT_FAILURE);
	}
}
