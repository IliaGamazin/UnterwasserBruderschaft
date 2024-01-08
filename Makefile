CC := gcc
CFLAGS := -std=gnu17 -lm -l SDL2 -l SDL2_image -l SDL2_mixer

executable:
	$(CC) $(CFLAGS) -o $@ ./src/*.c

