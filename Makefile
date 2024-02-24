CC := clang
CFLAGS := -std=c11 -Wall -Wextra -Werror -Wpedantic
LIBS := -lm -lSDL2 -lSDL2_image -lSDL2_mixer

EXECUTABLE := endgame

all: $(EXECUTABLE)

$(EXECUTABLE): $(wildcard ./inc/*.h) $(wildcard ./src/*.c)
	mkdir -p ./obj
	$(CC) $(CFLAGS) -c ./src/*.c
	mv ./*.o ./obj
	$(CC) $(LIBS) $(CFLAGS) -o $(EXECUTABLE) ./obj/*.o

uninstall:
	rm -rf ./obj
	rm -rf ./$(EXECUTABLE)

clean:
	rm -rf ./obj

reinstall: uninstall all

