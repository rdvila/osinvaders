#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#include <SDL.h>

#define logic_decrement_my_spaceship_xvel(d) \
	logic_change_my_spaceship_xvel(d, -1);

#define logic_increment_my_spaceship_xvel(d) \
	logic_change_my_spaceship_xvel(d, 1);

typedef enum {
	LG_DIRECTION_LEFT,
	LG_DIRECTION_RIGHT,

} Direction;

void logic_move_my_spaceship(void);
void logic_change_my_spaceship_xvel(Direction direction, int mul);
void logic_check_collision_screen_my_spaceship();

void logic_make_my_spaceship_shoot(unsigned limit);
void logic_move_my_shots();
void logic_check_collision_screen_my_shots();

void logic_move_my_enemies(void);
void logic_change_enemies_direction();
void logic_check_collision_screen_enemies();

SDL_bool logic_has_collision_rect(SDL_Rect *a, SDL_Rect *b);
unsigned logic_has_collision_my_shots();
void logic_change_enemies_xvel();

void logic_check_collision_my_shots_barriers();
void logic_check_collision_enemies_barriers();

void logic_make_enemies_shoot(unsigned limit);
void logic_move_enemies_shots();
void logic_check_collision_screen_enemies_shots();

void logic_check_collision_my_spaceship_enemies_shots();
void logic_check_collision_barrier_enemies_shots();

#endif /*LOGIC_H_INCLUDED*/
