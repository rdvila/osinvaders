#ifndef SCREEN_INCLUDED
#define SCREEN_INCLUDED

#include <SDL.h>

#define MAX_SCREEN      8

#define SCREEN_SPLASH   0
#define SCREEN_MENU     1
#define SCREEN_GAME     2
#define SCREEN_CODE     3
#define SCREEN_OPTIONS  4
#define SCREEN_PAUSE    5
#define SCREEN_CONTINUE 6
#define SCREEN_GAMEOVER 7

typedef int  (*init_f)(void);
typedef void (*quit_f)(void);
typedef int  (*loop_f)(void);

typedef struct {
	init_f init;
	quit_f quit;
	loop_f loop;
	SDL_bool initialized;

} Screen;

Screen *screens;

int screen_init(void);
int screen_loop(void);

#endif /*SCREEN_INCLUDED*/
