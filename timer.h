#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <SDL.h>

Uint32 start_ticks;
Uint32 pause_ticks;

SDL_bool started;
SDL_bool paused;


void timer_init_default(void);

void timer_start(void);
void timer_stop(void);
void timer_pause(void);
void timer_unpause(void);
void timer_delay(void);

Uint32 timer_get_ticks(void);

#endif /*TIMER_H_INCLUDED*/
