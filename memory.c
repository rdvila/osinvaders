#include "memory.h"

void *memory_alloc(size_t bytes)
{
	void *obj = SDL_malloc(bytes);
	SDL_memset(obj, 0, bytes);
	return obj;		
}


void memory_free(void *pointer)
{
	SDL_free(pointer);
}
