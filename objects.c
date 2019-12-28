#include "objects.h" 

#include "memory.h"

int objects_init(void)
{
	enemies_xvel = 1;
	enemies_yvel = 2;
	num_visibles = (MAX_EROWS * MAX_ECOLS);

	int i;
	for (i=0; i < MAX_EROWS; i++) {
		x_rows[i] = 18 * F;
		y_rows[i] = 24 * F;
	}
	
	x_rows[0] = 20 * F;

	objects_init_my_spaceship();
	objects_init_my_shots();
	objects_init_enemies();
	objects_init_enemies_shots();
	objects_init_enemies_mship();
	objects_init_objectsinfo();
	objects_init_barriers();
	return 0;
}

void objects_quit(void)
{
	objects_quit_objectsinfo();
	objects_quit_my_spaceship();
	objects_quit_my_shots();
	objects_quit_enemies();
	objects_quit_barriers();
}

void objects_draw_my_spaceship()
{
	graphics_apply_graphic_object(my_spaceship->graphic_obj);
}

void objects_quit_my_spaceship()
{
	memory_free(my_spaceship->graphic_obj);
	memory_free(my_spaceship);
}

void objects_quit_my_shots()
{
	int i;
	for (i=0; i < MAX_SHOTS; i++) {
		memory_free(my_shots[i]->graphic_obj);
		memory_free(my_shots[i]);
	}
}

void objects_quit_enemies()
{
	int i;
	for (i=0; i < MAX_EROWS; i++) {
		int j;
		for (j = 0; j < MAX_ECOLS; j++) {
			memory_free(enemies[i][j]->graphic_obj);
			memory_free(enemies[i][j]);
		}
		
	}
}

void objects_init_my_spaceship()
{
	static GameObject *obj;

	obj = memory_alloc(sizeof(GameObject));
	my_spaceship = obj;	

	obj->sprites[0] = sprites_get(6);	
	obj->sprites[1] = sprites_get(20);	
	obj->sprites[2] = sprites_get(21);
	obj->sprites_count = 3;
	
	static GraphicObject *gobj;
	gobj = memory_alloc(sizeof(GraphicObject));
	obj->graphic_obj = gobj;

	gobj->sprite = obj->sprites[0];
	gobj->x = mget_center_x(gobj);
	gobj->y = mget_screen_h - (19 * F);
	gobj->w = gobj->sprite->w;
	gobj->h = gobj->sprite->h;
	gobj->visible = SDL_TRUE;
}

void objects_init_my_shots()
{
	int i;
	for (i=0; i<MAX_SHOTS; i++) {
		static GameObject *obj;

		obj = memory_alloc(sizeof(GameObject));
		my_shots[i] = obj;	

		obj->sprites[0] = sprites_get(65);	
		obj->sprites_count = 1;
		obj->yvel = (-4 * F);
	
		static GraphicObject *gobj;

		gobj = memory_alloc(sizeof(GraphicObject));
		obj->graphic_obj = gobj;

		gobj->sprite = obj->sprites[0];
		gobj->w = gobj->sprite->w; 
		gobj->h = gobj->sprite->h;
	}
}

void objects_draw_my_shots()
{
	int i;
	for (i=0; i< MAX_SHOTS; i++) {
		graphics_apply_graphic_object(my_shots[i]->graphic_obj);
	}
}

static void new_enemy(GameObject *obj, int sprite1, int sprite2)
{
	obj->sprites[0] = sprites_get(sprite1);
	obj->sprites[1] = sprites_get(sprite2);
	obj->sprites[2] = sprites_get(19);
	obj->sprites_count = 3;

	static GraphicObject *gobj;
	gobj = memory_alloc(sizeof(GraphicObject));
	obj->graphic_obj = gobj;

	gobj->sprite = obj->sprites[0];
	gobj->w = gobj->sprite->w; 
	gobj->h = gobj->sprite->h; 
	gobj->visible = SDL_TRUE;
}

static void set_enemy_position(int r, int c, int x ,int y)
{
	static GraphicObject *obj;

	obj = enemies[r][c]->graphic_obj;
	obj->x = x;
	obj->y = (y * F);
}
		

static void init_enemies_position()
{
	int i, rx = 0;
	for (i = 0; i < MAX_ECOLS; i++) {
		set_enemy_position(0, i, rx , 0);
		set_enemy_position(1, i, rx , 16);
		set_enemy_position(2, i, rx , 32);
		set_enemy_position(3, i, rx , 48);
		
		rx += (16 * F);
	}
}

void objects_init_enemies()
{
	int i;
	for (i = 0; i < MAX_ECOLS; i++) {
		static GameObject *obj;

		/*row 1*/
		obj = memory_alloc(sizeof(GameObject));
		enemies[0][i] = obj;
		new_enemy(obj, 1, 0);

		/*row 2*/
		obj = memory_alloc(sizeof(GameObject));
		enemies[1][i] = obj;
		new_enemy(obj, 3, 2);

		/*row 3*/
		obj = memory_alloc(sizeof(GameObject));
		enemies[2][i] = obj;
		new_enemy(obj, 4, 5);

		/*row 4*/
		obj = memory_alloc(sizeof(GameObject));
		enemies[3][i] = obj;
		new_enemy(obj, 5, 4);
	}

	init_enemies_position();
}

static void new_objectinfo(GraphicObject *obj, int sprite)
{
	obj->sprite = sprites_get(sprite);
	obj->w = obj->sprite->w;
	obj->h = obj->sprite->h;
	obj->visible = SDL_TRUE;
}

void objects_init_objectsinfo()
{
	static GraphicObject *obj;

	/*P1 <     >*/
	obj = memory_alloc(sizeof(GraphicObject));
	p1 = obj;

	new_objectinfo(obj, 9);
	obj->x = (4 * F);
	obj->y = (1 * F);
	
	/*H1 <     >*/
	obj = memory_alloc(sizeof(GraphicObject));
	h1 = obj;

	new_objectinfo(obj, 32);
	obj->x = (91 * F);
	obj->y = (1 * F);
	
	/*lifes*/
	obj = memory_alloc(sizeof(GraphicObject));
	lifes = obj;

	new_objectinfo(obj, 35);
	obj->x = (17 * F);
	obj->y = mget_screen_h - mget_sprite_h(35);
	
	/*credits*/
	obj = memory_alloc(sizeof(GraphicObject));
	credits = obj;

	new_objectinfo(obj, 34);
	obj->x = (97 * F);
	obj->y = mget_screen_h - mget_sprite_h(34);
	
	/*______________*/
	obj = memory_alloc(sizeof(GraphicObject));
	bar = obj;

	new_objectinfo(obj, 33);
	obj->x = 0;
	obj->y = mget_screen_h - (9 * F);

	int i, x1 = (24 * F), x2 = (112 * F);
	for (i=0; i< MAX_NUM; i++) {
		/*score*/
		obj = memory_alloc(sizeof(GraphicObject));
		p1_num[i] = obj;

		new_objectinfo(obj, 22);
		obj->x = x1;
		obj->y = (1 * F);
		x1+= (3 * F) + (5 * F);
		
		/*hscore*/
		obj = memory_alloc(sizeof(GraphicObject));
		h1_num[i] = obj;

		new_objectinfo(obj, 22);
		obj->x = x2;
		obj->y = (1 * F);
		x2 += (3 * F) + (5 * F);
	} 
	
	/*lifes num*/
	obj = memory_alloc(sizeof(GraphicObject));
	lifes_num = obj;

	new_objectinfo(obj, 22);
	obj->x = (9 * F);
	obj->y = mget_screen_h - mget_sprite_h(22);
	
	/*credits num*/
	obj = memory_alloc(sizeof(GraphicObject));
	credits_num = obj;

	new_objectinfo(obj, 22);
	obj->x = (145 * F);
	obj->y = mget_screen_h - mget_sprite_h(22);
}

void objects_quit_objectsinfo()
{

	memory_free(p1);	
	memory_free(h1);	
	memory_free(bar);	
	memory_free(credits);	
	memory_free(lifes);
	memory_free(lifes_num);
	memory_free(credits_num);	

	int i;
	for (i=0; i< MAX_NUM; i++) {
		memory_free(p1_num[i]);	
		memory_free(h1_num[i]);
	}
}

void objects_draw_objectsinfo()
{
	graphics_apply_graphic_object(p1);	
	graphics_apply_graphic_object(h1);	
	graphics_apply_graphic_object(bar);	
	graphics_apply_graphic_object(credits);	
	graphics_apply_graphic_object(lifes);

	int i;
	for (i=0; i< MAX_NUM; i++) {
		graphics_apply_graphic_object(p1_num[i]);	
		graphics_apply_graphic_object(h1_num[i]);
	}	
	
	graphics_apply_graphic_object(credits_num);	
	graphics_apply_graphic_object(lifes_num);
}

static void enemy_apply(int r, int c)
{
	GraphicObject *obj = enemies[r][c]->graphic_obj;
	graphics_apply_graphic_object_xy(obj,
		obj->x + (x_rows[r]),
		obj->y + (y_rows[r]));
	
}

void objects_draw_enemies()
{
	objects_animate_enemies_y();

	int i;
	for (i = 0; i < MAX_ECOLS; i++) {
		 enemy_apply(0, i);
		 enemy_apply(1, i);
		 enemy_apply(2, i);
		 enemy_apply(3, i);
	}
}

void objects_animate_enemies_y()
{
	static unsigned count_enemy_y;
	if (anim_enemies_y) {
		y_rows[count_enemy_y % MAX_EROWS] += 
				(enemies_yvel * F);

		if ((count_enemy_y % MAX_EROWS) >= (MAX_EROWS -1)) {
			anim_enemies_y = SDL_FALSE;
		}

		count_enemy_y += 1;
	}
}

void new_barrier(Barrier *bar, int x)
{
	bar->x = x;
	bar->y = (mget_screen_h - (48 * F));

	int i, n = 66;
	for (i=0; i < MAX_PIECES; i++) {
		GraphicObject *obj = memory_alloc(sizeof(GraphicObject));
		bar->pieces[i] = obj;
		
		obj->sprite = sprites_get(n++);
		obj->x = bar->x + obj->sprite->x;
		obj->y = bar->y + obj->sprite->y;

		obj->w = obj->sprite->w;
		obj->h = obj->sprite->h;
		obj->visible = SDL_TRUE;
	}
}

void objects_init_barriers()
{
	int i;
	int x_pos[MAX_BARR] = {9, 49, 89, 129};

	for (i=0; i < MAX_BARR; i++) {
		static Barrier *bar;

		bar = memory_alloc(sizeof(Barrier));
		new_barrier(bar, x_pos[i] * F);
		barriers[i] = bar;
	}
	
}

static void draw_barrier(Barrier *bar)
{
	int i;
	for (i=0; i < MAX_PIECES; i++) {
		GraphicObject *obj = bar->pieces[i];
		graphics_apply_graphic_object_xy(obj, obj->x, obj->y);
	}
}

void objects_draw_barriers()
{
	int i;
	for (i=0; i < MAX_BARR; i++) {
		draw_barrier(barriers[i]);
	}
}

static void free_barrier_pieces(Barrier *bar)
{
	int i;
	for (i=0; i < MAX_PIECES; i++) {
		memory_free(bar->pieces[i]);
	}	
}

void objects_quit_barriers()
{
	int i;
	for (i=0; i < MAX_BARR; i++) {
		free_barrier_pieces(barriers[i]);
		memory_free(barriers[i]);
	}
}

void objects_rebuild_barriers()
{
	int i, j;
	for (i=0; i < MAX_BARR; i++) {
		for (j=0; j < MAX_PIECES; j++) {
			barriers[i]->pieces[j]->visible = SDL_TRUE;	
		}
	}
}

void objects_init_enemies_shots()
{	
	int i;
	for (i=0; i < MAX_ESHOTS; i++) {
		static GameObject *obj;
		obj = memory_alloc(sizeof(GameObject));
		enemies_shots[i] = obj;
		obj->yvel = 8;
		obj->points = 1;

		static GraphicObject *gobj;
		gobj = memory_alloc(sizeof(GraphicObject));
		obj->graphic_obj = gobj;
	}
}

void objects_draw_enemies_shots()
{
	int i;
	for (i=0; i < MAX_ESHOTS; i++) {
		GameObject *obj = enemies_shots[i];

		if (!obj->graphic_obj->visible)
			continue;

		graphics_apply_graphic_object(obj->graphic_obj);
	}
}

void objects_quit_enemies_shots()
{
	int i;
	for (i=0; i < MAX_ESHOTS; i++) {
		memory_free(enemies_shots[i]->graphic_obj);
		memory_free(enemies_shots[i]);
	}
}

void objects_init_enemies_mship()
{
}

void objects_draw_enemies_mship()
{
}

void objects_quit_enemies_mship()
{
}

