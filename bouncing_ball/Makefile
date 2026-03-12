CC = gcc
CFLAGS = -Wall -Wextra 
DEBUG_CFLAGS = -DDEBUG -g -O0 -fsanitize=address

LFLAGS = -L ./lib/ -lraylib -lm

all: run

run: clock
	./bouncing_ball

clock: 
	$(CC) -o bouncing_ball bouncing_ball.c $(CFLAGS) $(LFLAGS)

debug:
	$(CC) -o bouncing_ball bouncing_ball.c $(CFLAGS) $(LFLAGS) $(DEBUG_FLAGS)

clean: 
	rm -rf bouncing_ball

