#ifndef SPRITES_H_INCLUDED
#define SPRITES_H_INCLUDED

#include <SDL.h>

#define DATA_DIR "data/"

#define SPRITE_FILE_1X "invaders_1x.png"
#define SPRITE_FILE_2X "invaders_2x.png"
#define SPRITE_FILE_4X "invaders_4x.png"

#define F factor

unsigned factor;
char *sprite_file;

SDL_Rect *sprites;
SDL_Rect *sprites_1x;
SDL_Rect *sprites_2x;
SDL_Rect *sprites_4x;

int sprites_init(unsigned mode);

void sprites_init_1x(void);
void sprites_init_2x(void);
void sprites_init_4x(void);

SDL_Rect *sprites_get(unsigned index);

#endif /* SPRITES_H_INCLUDED */
