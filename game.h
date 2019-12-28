#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

typedef enum {
	GAME_PLAY,
	GAME_PAUSE,
	GAME_OVER,
	GAME_CONTINUE,
	GAME_LEAVE,
	GAME_QUIT,

} GameState;

unsigned int level;
unsigned int credits_left;
unsigned int lifes_left;
unsigned int my_shots_limit;
unsigned int enemies_shots_limit;
GameState game_state;
int score;
int hscore;

int  game_init(void);
void game_quit(void);
int  game_loop(void);

void game_draw(void);
void game_handle(void);

#endif /* GAME_H_INCLUDED */
