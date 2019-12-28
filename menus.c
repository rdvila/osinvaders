#include "menus.h"

#include "memory.h"
#include "controls.h"
#include "timer.h"
#include "screen.h"


static void new_menu(GraphicObject *menu, int sprite, int yadd)
{
	menu->sprite = sprites_get(sprite);
	menu->x = mget_center_x(menu); 
	menu->y = mget_center_y(menu) + yadd; 
	menu->w = menu->sprite->w; 
	menu->h = menu->sprite->h; 
	menu->visible = SDL_TRUE;
} 

void menus_init_menus()
{
	GraphicObject *menu = NULL;

	/*Menu START*/
	menu =  memory_alloc(sizeof(GraphicObject));
	menus[0] = menu;
	new_menu(menu, 51, 0);
	
	/*Menu CODE*/
	menu = memory_alloc(sizeof(GraphicObject));
	menus[1] = menu;
	new_menu(menu, 52, mget_sprite_h(52)  + (F * 4));

	/*Menu OPTIONS*/
	menu = memory_alloc(sizeof(GraphicObject));
	menus[2] = menu;
	new_menu(menu, 53, (mget_sprite_h(53) * 2)  + (F * 8));

	/*Menu QUIT*/
	menu = memory_alloc(sizeof(GraphicObject));
	menus[3] = menu;
	new_menu(menu, 62, (mget_sprite_h(62) * 3) + (F * 12));
}

static void new_menu_bk(GraphicObject *bk, int sprite, int parent, int yadd)
{
	bk->sprite  = sprites_get(sprite);
	bk->visible = SDL_TRUE;
	bk->x = menus[parent]->x;
	bk->y = menus[parent]->y + yadd;
}

void menus_init_background_menus()
{
	GraphicObject *bk = NULL;

	/*Menu bk 1-1*/
	bk = memory_alloc(sizeof(GraphicObject));
	menus_bk1[0] = bk;
	new_menu_bk(bk, 54, 0, 0);

	/*Menu bk 1-2*/
	bk = memory_alloc(sizeof(GraphicObject));
	menus_bk1[1] = bk;
	new_menu_bk(bk, 55, 1, 0);

	/*Menu bk 1-3*/
	bk = memory_alloc(sizeof(GraphicObject));
	menus_bk1[2] = bk;
	new_menu_bk(bk, 56, 2, 0);

	/*Menu bk 1-4*/
	bk = memory_alloc(sizeof(GraphicObject));
	menus_bk1[3] = bk;
	new_menu_bk(bk, 63, 3, 0);

	/*Menu bk 2-1*/
	bk = memory_alloc(sizeof(GraphicObject));
	menus_bk2[0] = bk;
	new_menu_bk(bk, 57, 0, menus[0]->h);

	/*Menu bk 2-2*/
	bk = memory_alloc(sizeof(GraphicObject));
	menus_bk2[1] = bk;
	new_menu_bk(bk, 58, 1, menus[1]->h);

	/*Menu bk 2-3*/
	bk = memory_alloc(sizeof(GraphicObject));
	menus_bk2[2] = bk;
	new_menu_bk(bk, 59, 2, menus[2]->h);

	/*Menu bk 2-4*/
	bk = memory_alloc(sizeof(GraphicObject));
	menus_bk2[3] = bk;
	new_menu_bk(bk, 64, 3, menus[3]->h);
} 

void menus_draw()
{
	graphics_erase_screen();
	menus_background_animation();

	int i;
	for (i=0; i < MAX_MENUS; i++) {
		graphics_apply_graphic_object(menus[i]);
	}

	graphics_flip_screen();	
}

void menus_handle()
{
	static SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case (GK_UP):
				menus_next(MAX_MENUS -1);
				break;
			case (GK_DOWN):
				menus_next(1);
				break;
			case (GK_START):
			case (GK_A):
				menus_select_option();
				break;

			default: break;
			}	
		}
		else if (event.type == SDL_QUIT) {
			menu_option = MENU_QUIT;
		}
	}
}

void menus_next(int index)
{
	unsigned new_index  = (curr_index+index) % MAX_MENUS;

	menus_bk1[curr_index]->visible = SDL_FALSE;
	menus_bk2[curr_index]->visible = SDL_FALSE;

	curr_index = new_index;

	menus_start = SDL_GetTicks();
}

int menus_init(void)
{
	menu_option = MENU_LOOP;
	curr_index  = 0;

	menus_init_menus();
	menus_init_background_menus();
	return 0;
}

void menus_select_option()
{
	switch (curr_index) {
	case 0:
		menu_option = MENU_PLAY;
		break;
	case 1:
		menu_option = MENU_CODE;
		break;
	case 2:
		menu_option = MENU_OPTIONS;
		break;
	case 3:
		menu_option = MENU_QUIT;
		break;
	}
}

void menus_background_animation()
{
	if (!(menus_count % 4)) {
		GraphicObject *obj = menus_bk1[curr_index];

		if ((SDL_GetTicks() - menus_start) > 4000) {
			obj = menus_bk2[curr_index];
		}
		obj->visible = SDL_TRUE;
		graphics_apply_graphic_object(obj);
	}

	menus_count += 1;
}

void menus_quit(void)
{
	int i;
	for (i=0; i<MAX_MENUS; i++) {
		memory_free(menus_bk1[i]);
		menus_bk1[i] = NULL;

		memory_free(menus_bk2[i]);
		menus_bk2[i] = NULL;

		memory_free(menus[i]);
		menus[i] = NULL;
	}
}

int menus_loop(void)
{

	menus_start = SDL_GetTicks();

	while (1) {
		timer_start();

		menus_handle();
		menus_draw();
		
		timer_delay();

		switch (menu_option) {
		case MENU_PLAY:
			return SCREEN_GAME; 
		case MENU_CODE:
			return SCREEN_CODE;
		case MENU_OPTIONS:
			return SCREEN_OPTIONS;
		case MENU_LOOP:
			continue;
		case MENU_QUIT:
			exit(0);
		}

	}

	return 0;
}
