#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>

#include "settings.h"
#include "sprites.h"

#define mget_screen_w (screen_width)
#define mget_screen_h (screen_height)

#define mget_center_x(go) \
	((mget_screen_w / 2) - (go->sprite->w / 2))

#define mget_center_y(go) \
	((mget_screen_h / 2) - (go->sprite->h / 2))

#define mget_sprite_w(n) (sprites[n].w)
#define mget_sprite_h(n) (sprites[n].h)

#define graphics_apply_graphic_object(obj) \
	graphics_apply_graphic_object_xy(obj, obj->x, obj->y)

#define graphics_is_equal_color_xy(s, x, y, c) \
	(graphics_get_pixel_color_xy(s,x, y) == c)


typedef enum {
	CC_RGB_BLACK,
	CC_RGB_RED,
	CC_RGB_GREEN,
	CC_RGB_BLUE,
	CC_RGB_WHITE,

} CommonColor;

SDL_Surface *graphics;
SDL_Surface *screen;

typedef struct {
	SDL_Rect *sprite;

	Sint16 x, y;
	Uint16 w, h;

	SDL_bool visible;
	
} GraphicObject;

int graphics_init(void);

SDL_Surface *surface_load_image(const char *name);
SDL_Surface *surface_create_empty(SDL_Surface *src, unsigned w, unsigned h);
	
void graphics_apply_surface(int x, int y, SDL_Surface *src,
		SDL_Surface *dest, SDL_Rect *clip);

void graphics_apply_graphic_object_xy(GraphicObject *obj, int x, int y);

void graphics_flip_screen(void);
void graphics_erase_screen(void);
void graphics_delay_screen(void);

Uint32 graphics_get_pixel_color_xy(SDL_Surface *surface, int x, int y);
void graphics_put_pixel_color_xy(SDL_Surface *surface, int x, int y,
		Uint32 pixel);

Uint32 graphics_get_uint32_from_common_color(CommonColor color);

#endif /* GRAPHICS_H_INCLUDED */
