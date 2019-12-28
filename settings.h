#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include <SDL.h>

unsigned screen_mode;
unsigned screen_width;
unsigned screen_height;
unsigned screen_bpp;
unsigned screen_fps;
unsigned screen_flags;

SDL_bool fullscreen;
SDL_bool enable_sound;


void settings_init_default(void);

void settings_set_mode(unsigned mode);

#endif /*SETTINGS_H_INCLUDED*/
