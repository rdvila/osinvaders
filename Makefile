CC=gcc
CFLAGS=-Wall -O2 -I/usr/include/SDL
LDFLAGS=-lSDL -lSDL_image

OBJS=game.o invaders.o main.o menus.o settings.o splash.o timer.o graphics.o logic.o memory.o objects.o sound.o sprites.o screen.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUG)

osinvaders: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm osinvaders *.o
