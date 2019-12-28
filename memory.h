#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include <string.h>
#include <SDL.h>

void *memory_alloc(size_t bytes);
void  memory_free(void *pointer);

#endif /*MEMORY_H_INCLUDED*/
