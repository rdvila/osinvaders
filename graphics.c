#include "graphics.h"

int graphics_init(void)
{
	graphics = surface_load_image(sprite_file);
	return 0;
}

SDL_Surface *surface_load_image(const char *name)
{
	static SDL_Surface *loadedimage;
	static SDL_Surface *optimizedimage;

	loadedimage = IMG_Load(name);

	if (!loadedimage) {
		fprintf(stderr, "Could not load image %s: %s\n",
			name, SDL_GetError());
		exit(EXIT_FAILURE);
	}

	optimizedimage = SDL_DisplayFormat(loadedimage);
	SDL_FreeSurface(loadedimage);

	if (!loadedimage) {
		fprintf(stderr, "Could optimize image: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_SetColorKey(optimizedimage, SDL_SRCCOLORKEY,
		SDL_MapRGB(optimizedimage->format, 0, 0, 0));

	return optimizedimage;
}

SDL_Surface *surface_create_empty(SDL_Surface *src, unsigned w, unsigned h)
{
	static SDL_Surface     *surface;
	static SDL_PixelFormat *pixel;
	Uint8 alpha = 0; 

	pixel = src->format;
	if (src->flags & SDL_SRCCOLORKEY) {
		alpha = pixel->Amask;
	}

	surface = SDL_CreateRGBSurface(src->flags, w, h, pixel->BitsPerPixel,
		pixel->Rmask, pixel->Gmask, pixel->Bmask, alpha);

	if (!surface) {
		fprintf(stderr, "Cannot CreateRGBSurface: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	return surface; 
}


void graphics_apply_surface(int x, int y, SDL_Surface *src,
		SDL_Surface *dest, SDL_Rect *clip)
{
	static SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	if (SDL_BlitSurface(src, clip, dest, &offset) == -1) {
		fprintf(stderr, "Could not blit surface: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}	
}

void graphics_apply_graphic_object_xy(GraphicObject *obj, int x, int y)
{
	if (!obj->visible) return;

	graphics_apply_surface(x, y, graphics,
		screen, obj->sprite);
	
}

void graphics_flip_screen(void)
{
	if (SDL_Flip(screen) == -1) {
		fprintf(stderr, "Could not flip screen: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

void graphics_erase_screen(void)
{
	SDL_Surface *sc = screen;

	SDL_FillRect(sc, &sc->clip_rect,
			SDL_MapRGB(sc->format, 0, 0, 0));
}

Uint32 graphics_get_pixel_color_xy(SDL_Surface *surface, int x, int y)
{
	Uint32 *pixels = (Uint32 *)surface->pixels;
	return pixels[y * surface->w + x];
}

void graphics_put_pixel_color_xy(SDL_Surface *surface, int x, int y,
		Uint32 pixel)
{
	Uint32 *pixels = (Uint32 *)surface->pixels;
	pixels[y * surface->w + x] = pixel;
}

Uint32 graphics_get_uint32_from_common_color(CommonColor color)
{
	switch (color) {
	#if SDL_BYTE_ORDER == SDL_BIG_ENDIAN
	case CC_RGB_BLACK:
		return 0x00000000;
	case CC_RGB_RED:
		return 0xff000000;
	case CC_RGB_GREEN:
		return 0x00ff0000;
	case CC_RGB_BLUE:
		return 0x0000ff00;
	#else
	case CC_RGB_BLACK:
		return 0x00000000;
	case CC_RGB_RED:
		return 0x000000ff;
	case CC_RGB_GREEN:
		return 0x0000ff00;
	case CC_RGB_BLUE:
		return 0x00ff0000;
	case CC_RGB_WHITE:
		return 0x00ffffff;
	#endif
	}

	return 0;
}
