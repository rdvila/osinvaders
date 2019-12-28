#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#define MAX_MENUS 4

#include <SDL.h>

#include "graphics.h"

typedef enum {
	MENU_LOOP,
	MENU_PLAY,
	MENU_CODE,
	MENU_OPTIONS,

	MENU_QUIT,

} MenuOption;

MenuOption menu_option;
unsigned curr_index;
GraphicObject *menus[MAX_MENUS];
GraphicObject *menus_bk1[MAX_MENUS];
GraphicObject *menus_bk2[MAX_MENUS];
Uint32 menus_start;
Uint32 menus_count;

int  menus_init(void);
void menus_quit(void);
int  menus_loop(void);


void menus_init_menus();
void menus_init_background_menus();
void menus_draw();
void menus_handle();
void menus_next(int index);
void menus_select_option();
void menus_background_animation();

#endif /* MENU_H_INCLUDED */
