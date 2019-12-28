#include "game.h"

#include "controls.h"
#include "timer.h"
#include "graphics.h"
#include "objects.h"
#include "logic.h"

int game_init(void)
{
	my_shots_limit      = 1;
	enemies_shots_limit = 1;
	if (objects_init() < 0);
		//TODO check error

	return 0;
}



void game_quit(void)
{
	objects_quit();
}

void game_draw(void)
{
	graphics_erase_screen();

	objects_draw_objectsinfo();
	objects_draw_barriers();

	objects_draw_my_spaceship();
	objects_draw_enemies();
	objects_draw_enemies_shots();
	
	objects_draw_my_shots();
	graphics_flip_screen();
}

void game_handle(void)
{
	static SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case (GK_LEFT):
				logic_increment_my_spaceship_xvel(
					LG_DIRECTION_LEFT);
				break;
			case (GK_RIGHT):
				logic_increment_my_spaceship_xvel(
					LG_DIRECTION_RIGHT);
				break;

			case (GK_Y):
				logic_make_my_spaceship_shoot( my_shots_limit);
				break;

			default: break;
			}
		}

		else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
			case (GK_LEFT):
				logic_decrement_my_spaceship_xvel(
					LG_DIRECTION_LEFT);
				break;
			case (GK_RIGHT):
				logic_decrement_my_spaceship_xvel(
					LG_DIRECTION_RIGHT);
				break;

			default: break;
			}
		}

		else if (event.type == SDL_QUIT)
			game_state = GAME_QUIT;
	}
}

int game_loop()
{
	while (1) {
		timer_start();
		game_handle();
		
		logic_move_my_spaceship();
		logic_move_my_shots();

		logic_make_enemies_shoot(enemies_shots_limit);
		logic_move_enemies_shots();

		logic_move_my_enemies();
		score += logic_has_collision_my_shots(); 

		logic_check_collision_barrier_enemies_shots();
		logic_check_collision_my_spaceship_enemies_shots();

		game_draw();
		timer_delay();

		if (game_state == GAME_QUIT)
			exit(0);
	}
}
