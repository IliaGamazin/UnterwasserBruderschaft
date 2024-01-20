CC := gcc
CFLAGS := -std=gnu17 -Wall -pedantic
LIBS := -lSDL2 -lSDL2_image -lSDL2_mixer -lm
SRC := $(wildcard ./src/*.c)

executable: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
