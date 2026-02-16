CC = gcc
CFLAGS = -Wall -Wextra 
DEBUG_CFLAGS = -DDEBUG -g -O0 -fsanitize=address

LFLAGS = -L ./lib/ -lraylib -lm

all: run

run: clock
	./raindrops

clock: 
	$(CC) -o raindrops raindrops.c $(CFLAGS) $(LFLAGS)

debug:
	$(CC) -o raindrops raindrops.c $(CFLAGS) $(LFLAGS) $(DEBUG_FLAGS)

clean: 
	rm -rf raindrops

