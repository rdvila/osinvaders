#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

#include <SDL.h>

#include "graphics.h"

#define MAX_SPRITES 4
#define MAX_EROWS   4
#define MAX_ECOLS   8
#define MAX_ESHOTS  16
#define MAX_SHOTS   4
#define MAX_NUM     5
#define MAX_BARR    4
#define MAX_PIECES  37

typedef struct {
	SDL_Rect *sprites[MAX_SPRITES];
	unsigned sprites_count;
	
	GraphicObject *graphic_obj;

	int points;
	int xvel, yvel;
	SDL_bool is_dead;

} GameObject;


GameObject *my_spaceship;
GameObject *my_shots[MAX_SHOTS];
GameObject *enemies[MAX_EROWS][MAX_ECOLS];
GameObject *enemies_shots[MAX_ESHOTS];
GameObject *enemies_mship;

int x_rows[MAX_EROWS];
int y_rows[MAX_EROWS];
int enemies_xvel;
int enemies_yvel;

SDL_bool anim_enemies_y;
unsigned num_visibles;


GraphicObject *p1;
GraphicObject *p1_num[MAX_NUM];
GraphicObject *h1;
GraphicObject *h1_num[MAX_NUM];
GraphicObject *bar;
GraphicObject *credits;
GraphicObject *credits_num;
GraphicObject *lifes;
GraphicObject *lifes_num;

typedef struct {
	int x, y;
	GraphicObject *pieces[MAX_PIECES];
	
} Barrier;

Barrier *barriers[MAX_BARR];	

int  objects_init(void);
void objects_quit(void);

void objects_init_my_spaceship();
void objects_draw_my_spaceship();
void objects_quit_my_spaceship();

void objects_init_my_shots();
void objects_draw_my_shots();
void objects_quit_my_shots();

void objects_init_enemies();
void objects_draw_enemies();
void objects_quit_enemies();

void objects_init_enemies_shots();
void objects_draw_enemies_shots();
void objects_quit_enemies_shots();

void objects_init_enemies_mship();
void objects_draw_enemies_mship();
void objects_quit_enemies_mship();

void objects_init_objectsinfo();
void objects_quit_objectsinfo();
void objects_draw_objectsinfo();

void objects_animate_enemies_y();

void objects_init_barriers();
void objects_rebuild_barriers();
void objects_quit_barriers();
void objects_draw_barriers();

#endif /*OBJECTS_H_INCLUDED*/
