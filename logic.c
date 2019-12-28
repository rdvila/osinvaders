#include "logic.h"

#include "memory.h"
#include "graphics.h"
#include "objects.h"


void logic_change_my_spaceship_xvel(Direction direction, int mul)
{
	if (direction == LG_DIRECTION_RIGHT) {
		my_spaceship->xvel += ((mget_sprite_w(6) / 6) * mul);
	}

	if (direction == LG_DIRECTION_LEFT) {
		my_spaceship->xvel -= ((mget_sprite_w(6) / 6) * mul);
	}
}

void logic_move_my_spaceship()
{
	#ifdef GAME_DEBUG
		printf("x    = %i\n",  my_spaceship->graphic_obj->x);		
		printf("xvel = %i\n",  my_spaceship->xvel);		
	#endif

	my_spaceship->graphic_obj->x +=
		 my_spaceship->xvel;

	logic_check_collision_screen_my_spaceship();
}

void logic_check_collision_screen_my_spaceship()
{
	GraphicObject *gobj = my_spaceship->graphic_obj;
	if (gobj->x < 0 || (gobj->x + gobj->w) > mget_screen_w) {
		gobj->x -= my_spaceship->xvel;
	}
}

void logic_make_my_spaceship_shoot(unsigned limit)
{
	int i;
	for (i = 0; i < limit; i++) {
		static GraphicObject *gobj;
		gobj = my_shots[i]->graphic_obj;

		if (gobj->visible) continue;		

		GraphicObject *mss = my_spaceship->graphic_obj;

		gobj->x = mss->x + (mss->w / 2) - ((1 * F) / 2)
				+ my_spaceship->xvel;

		gobj->y = mss->y;

		gobj->visible = SDL_TRUE;
		break;
	}
}

void logic_move_my_shots()
{
	int i;
	for (i=0; i<MAX_SHOTS; i++) {
		static GraphicObject *gobj;
		gobj = my_shots[i]->graphic_obj;

		if (!gobj->visible) continue;

		gobj->y += my_shots[i]->yvel;
	}
	
	logic_check_collision_my_shots_barriers();
	logic_check_collision_screen_my_shots();
}

void logic_check_collision_screen_my_shots()
{
	int i;
	for (i=0; i< MAX_SHOTS; i++) {
		GraphicObject *gobj = my_shots[i]->graphic_obj;

		if (!gobj->visible) continue;
	
		if (gobj->y < (9 * F)) {
			gobj->visible = SDL_FALSE;
		}
	}
}

void logic_move_my_enemies(void)
{
	if (anim_enemies_y) return;

	static unsigned enemy_count_x;
	int vel = enemies_xvel * F;

	SDL_bool has_good_vel = (abs(enemies_xvel) > 2);

	if (has_good_vel) {
		int i;
		for (i=0; i < MAX_EROWS; i++) {
			x_rows[i] += vel;
		}
	}
	else {
		x_rows[enemy_count_x % MAX_EROWS] += vel;
		enemy_count_x += 1;	
	}

	if (has_good_vel || !(enemy_count_x % MAX_EROWS)) {	
		logic_check_collision_screen_enemies();
	}
	
	logic_check_collision_enemies_barriers();
}

void logic_check_collision_screen_enemies()
{
	int i, j;
	for (i=0; i < MAX_EROWS; i++) {
		for (j=0; j < MAX_ECOLS; j++) {
			GraphicObject *obj = enemies[i][j]->graphic_obj;

			int objx = (obj->x + x_rows[i])
						+ (enemies_xvel * F);

			if (!obj->visible) continue;

			if ((objx <= 0) || ((objx + obj->w) >= mget_screen_w)) {
				enemies_xvel *= -1;
				anim_enemies_y = SDL_TRUE;
			}
		}
	}
}

SDL_bool logic_has_collision_rect(SDL_Rect *a, SDL_Rect *b)
{
	int la, lb;
	int ra, rb;
	int ta, tb;
	int ba, bb;

	la = a->x;
	ra = la + a->w;
	ta = a->y;
	ba = ta + a->h;
	
	lb = b->x;
	rb = lb + b->w;
	tb = b->y;
	bb = tb + b->h;

	return !(ba <= tb || ta >= bb || ra <= lb || la >= rb);
}


static void enemy_to_rect(SDL_Rect *r, GameObject *enemy, int row)
{
	GraphicObject *obj = enemy->graphic_obj;

	r->x = obj->x + x_rows[row];
	r->y = obj->y + y_rows[row];

	r->w = obj->w;
	r->h = obj->h;
}

static void graphic_object_to_rect(SDL_Rect *r, GraphicObject *obj)
{
	r->x = obj->x;
	r->y = obj->y;

	r->w = obj->w;
	r->h = obj->h;
}

static int has_collision_enemies(GameObject *obj)
{
	int i, j;
	for (i=0; i < MAX_EROWS; i++) {
		for (j=0; j < MAX_ECOLS; j++) {
			GameObject *enemy = enemies[i][j];

			if (!enemy->graphic_obj->visible) continue;

			static SDL_Rect r1;
			static SDL_Rect r2;
			
			graphic_object_to_rect(&r1, obj->graphic_obj);
			enemy_to_rect(&r2, enemy, i);

			if (logic_has_collision_rect(&r1, &r2)) {
				num_visibles -= 1;
				logic_change_enemies_xvel();

				enemy->graphic_obj->visible = SDL_FALSE;
				obj->graphic_obj->visible   = SDL_FALSE;
				return enemy->points;
			}
		}
	}

	return 0;	
}

unsigned logic_has_collision_my_shots()
{
	unsigned points = 0;

	int i;
	for (i=0; i < MAX_SHOTS; i++) {
		GameObject *shot = my_shots[i];
		
		if (!shot->graphic_obj->visible) continue;

		points += has_collision_enemies(shot);
	}

	return points;
}

void logic_change_enemies_xvel()
{
	/* ;D */
	switch (num_visibles) {
	case 9:
	case 8:
		goto increment;
	case 7:
		enemies_yvel = 3;
		goto increment;
		break;
	case 5:
	case 3:
		enemies_yvel = 4;
		goto increment;
		break;
	}
	
	goto endthis;

increment:

	enemies_xvel +=
		(enemies_xvel < 0 ? -1 : 1);

endthis:
	return;
}

static SDL_bool check_collision_rect_barriers(SDL_Rect *r1)
{
	SDL_bool has_collision = SDL_FALSE;

	int i, j;	
	for (i=0; i < MAX_BARR; i++) {
		Barrier *bar = barriers[i];

		for (j=0; j < MAX_PIECES; j++) {
			GraphicObject *obj = bar->pieces[j];

			if (!obj->visible) continue;

			static SDL_Rect r2;
			graphic_object_to_rect(&r2, obj);


			if (logic_has_collision_rect(r1, &r2)) {
				obj->visible  = SDL_FALSE;
				has_collision = SDL_TRUE; 
			}
		}
	}	

	return has_collision;
}

void logic_check_collision_my_shots_barriers()
{
	int i;
	for (i=0; i < MAX_SHOTS; i++) {
		GraphicObject *obj = my_shots[i]->graphic_obj;

		if (!obj->visible) continue;
	
		static SDL_Rect r1;
		graphic_object_to_rect(&r1, obj);
		
		r1.w = 1;
		r1.h = 1;

		if (check_collision_rect_barriers(&r1)) {
			obj->visible = SDL_FALSE;
			return;
		}

	}	
}

void logic_check_collision_enemies_barriers()
{
	int i, j;
	for (i = 0; i < MAX_EROWS; i++) {
		for (j=0; j < MAX_ECOLS; j++) {
			GameObject *obj = enemies[i][j];

			if (!obj->graphic_obj->visible) continue;

			static SDL_Rect r1;
			enemy_to_rect(&r1, obj, i);

			check_collision_rect_barriers(&r1);
		}
	}	
}

static void set_enemy_shot_xy(GraphicObject *obj)
{
	Uint32 ticks = SDL_GetTicks();

	static GraphicObject *enemy;
	Uint32 randr = ticks % MAX_EROWS;
	Uint32 randc = ticks % MAX_ECOLS;

	int i, j;
	for (i=0; i< MAX_EROWS; i++) {
		randr  += 1;
		randr  %= MAX_EROWS;

		for (j=0; j < MAX_ECOLS; j++) {
			randc  += 1;
			randc  %= MAX_ECOLS;
			
			enemy  = enemies[randr][randc]->graphic_obj;
		
			if (enemy->visible)
				goto end_this;

		}
	}

	return;

end_this:
	obj->x = (enemy->x + (enemy->w / 2) + enemies_xvel)
		+ x_rows[randr];

	obj->y = (enemy->y + enemy->h) + y_rows[randr];
} 

void logic_make_enemies_shoot(unsigned limit)
{
	if (num_visibles < 0) return;

	int i;
	for (i = 0; i < limit; i++) {
		GameObject    *obj  = enemies_shots[i];
		GraphicObject *gobj = obj->graphic_obj;

		if (gobj->visible) continue;

		int sprite = (SDL_GetTicks() % 2) ? 11 : 13;

		obj->sprites[0] = sprites_get(sprite);
		obj->sprites[1] = sprites_get(sprite+1);
		obj->sprites_count = 2;

		gobj->sprite = obj->sprites[0];

		gobj->w = obj->sprites[0]->w;
		gobj->h = obj->sprites[0]->h;
		gobj->visible = SDL_TRUE;

		set_enemy_shot_xy(gobj);
		return;
	}
}

void logic_move_enemies_shots()
{
	int i;
	for (i = 0; i < MAX_ESHOTS; i++) {
		GameObject    *obj  = enemies_shots[i];
		GraphicObject *gobj = obj->graphic_obj;

		if (!gobj->visible) continue;

		gobj->y += obj->yvel;
	}

	logic_check_collision_screen_enemies_shots();
}

void logic_check_collision_screen_enemies_shots()
{
	int i;
	for (i = 0; i < MAX_ESHOTS; i++) {
		GraphicObject *obj = enemies_shots[i]->graphic_obj;
		
		if (obj->y >= mget_screen_h) {
			obj->visible = SDL_FALSE;
		}
	}
}

static SDL_bool has_collision_rect_enemies_shots(SDL_Rect *rect)
{
	static SDL_Rect r1;

	int i;
	for (i = 0; i < MAX_ESHOTS; i++) {
		GraphicObject *obj = enemies_shots[i]->graphic_obj;

		if (!obj->visible) continue;

		graphic_object_to_rect(&r1, obj);

		if (logic_has_collision_rect(&r1, rect)) {
			obj->visible = SDL_FALSE;
			return SDL_TRUE;
		}
	}

	return SDL_FALSE;
}

void logic_check_collision_my_spaceship_enemies_shots()
{
	static SDL_Rect r1;
	GraphicObject *obj = my_spaceship->graphic_obj;

	graphic_object_to_rect(&r1, obj);
	
	if (has_collision_rect_enemies_shots(&r1))
		obj->visible = SDL_FALSE;
}

void logic_check_collision_barrier_enemies_shots()
{
	static SDL_Rect r1;

	int i;
	for (i = 0; i < MAX_ESHOTS; i++) {
		GraphicObject *obj = enemies_shots[i]->graphic_obj;

		if (!obj->visible) continue;

		graphic_object_to_rect(&r1, obj);
		if (check_collision_rect_barriers(&r1)) {
			obj->visible = SDL_FALSE;
		}
	}
}

