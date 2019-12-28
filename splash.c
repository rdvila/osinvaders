#include "splash.h"

#include "memory.h"
#include "controls.h"
#include "timer.h"
#include "screen.h"

int splash_init(void)
{
	splash_state = SPLASH_LOOP;

	static GraphicObject *obj;

	/*SPACE*/
	obj = memory_alloc(sizeof(GraphicObject));
	space = obj;	

	obj->sprite = sprites_get(60);
	obj->x = mget_center_x(obj);
	obj->y =  0 - obj->sprite->h; 
	obj->visible = SDL_TRUE;
	
	/*INVADERS*/
	obj = memory_alloc(sizeof(GraphicObject));
	invaders = obj;	

	obj->sprite = sprites_get(61);
	obj->x = mget_center_x(obj);
	obj->y = mget_screen_h;
	obj->visible = SDL_TRUE;
	return 0;
}

void splash_quit(void)
{
	memory_free(space);	
	memory_free(invaders);	
}

void splash_draw(void)
{
	graphics_erase_screen();

	splash_animation();
	
	graphics_apply_graphic_object(invaders);
	graphics_apply_graphic_object(space);
	
	graphics_flip_screen();
}

void splash_handle(void)
{
	static SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			splash_state = SPLASH_LEAVE;			
		}
		else if (event.type == SDL_QUIT) {
			exit(EXIT_SUCCESS);
		}
	}
}

int splash_loop(void)
{
	start = SDL_GetTicks();

	while (1) {
		timer_start();

		splash_handle();
		splash_draw();

		timer_delay();

		Uint32 currticks = SDL_GetTicks();
		if ((currticks - start) >= 10000) {
			splash_state = SPLASH_LEAVE;
		}

		if (splash_state == SPLASH_LEAVE)
			return SCREEN_MENU;
	}

	return 0;	
}

void splash_animation()
{
	if (invaders->y > ((mget_screen_h / 2) + 10 * F)) {
		space->y    += 1 * F;
		invaders->y -= 1 * F;
	}
}
