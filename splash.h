#ifndef SPLASH_H_INCLUDED
#define SPLASH_H_INCLUDED

#include <SDL.h>

#include "graphics.h"

GraphicObject *space;
GraphicObject *invaders;
Uint32 start;

typedef enum {
	SPLASH_LOOP,
	SPLASH_LEAVE,
} SplashState;

SplashState splash_state;

int  splash_init(void);
void splash_quit(void);
int  splash_loop(void);

void splash_draw(void);
void splash_handle(void);

void splash_animation();

#endif /*SPLASH_H_INCLUDED*/
