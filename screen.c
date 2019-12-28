#include "screen.h"

#include "splash.h"
#include "menus.h"
#include "game.h"

#include <stdio.h>


static Screen _screens[] = { 

	{splash_init, splash_quit, splash_loop, 0},
	{menus_init , menus_quit , menus_loop , 0},
	{game_init  , game_quit  , game_loop  , 0},
	{NULL, NULL, NULL, 0},
	{NULL, NULL, NULL, 0},
	{NULL, NULL, NULL, 0},
	{NULL, NULL, NULL, 0},
	{NULL, NULL, NULL, 0},
};

int screen_init()
{
	screens = _screens;
	return 0;
}

int screen_loop()
{
	int next_screen = 0;
	static Screen screen_curr;
	
	while (next_screen >= 0) {

		screen_curr = screens[next_screen];
	
		if (!screen_curr.initialized) {
			screen_curr.initialized = SDL_TRUE;
			screen_curr.init();
		}

		next_screen = screen_curr.loop();
		printf("%i\n", next_screen);
	}
	
	return 0;
}
