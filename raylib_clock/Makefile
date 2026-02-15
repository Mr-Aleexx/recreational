CC = gcc
CFLAGS = -Wall -Wextra 
DEBUG_CFLAGS = -DDEBUG -g -O0 -fsanitize=address

LFLAGS = -L ./lib/ -lraylib -lm

all: run

run: clock
	./raylib_clock

clock: 
	$(CC) -o raylib_clock raylib_clock.c $(CFLAGS) $(LFLAGS)

debug:
	$(CC) -o raylib_clock raylib_clock.c $(CFLAGS) $(LFLAGS) $(DEBUG_FLAGS)

clean: 
	rm -rf raylib_clock

