CC := clang
CFLAGS := -std=c17 -Wall -Wextra -Werror -Wpedantic
LIBS := -lSDL2 -lSDL2_image -lSDL2_mixer -lm
SRC := $(wildcard ./src/*.c)

executable: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

