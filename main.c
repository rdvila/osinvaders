#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "invaders.h"
#include "settings.h"
#include "graphics.h"

int main(int argc, char **argv)
{
	static SDL_Surface *main_screen;

	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		fprintf(stderr, "Could not init everything: %s\n",
			SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_WM_SetCaption("::: Open Space Invaders :::", NULL);

	settings_init_default();
	settings_set_mode(3);

	if (fullscreen) {
		screen_flags |= SDL_FULLSCREEN;
	}
		
	main_screen = SDL_SetVideoMode(screen_width, screen_height,
		screen_bpp, screen_flags);

	if (!main_screen) {
		fprintf(stderr, "Could not set video mode: %s\n",
			SDL_GetError());
		exit(EXIT_FAILURE);
	}

	/*;)*/
	screen = main_screen;

	invaders_init();
	invaders_loop();

	return 0;
}
