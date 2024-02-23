#pragma once
#ifndef LIBS_H
#define LIBS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_mouse.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define LEVEL_WIDTH 1920
#define LEVEL_HEIGHT 1080

#define BUTTON_COUNT_MENU 5
#define BUTTON_HEIGHT 60
#define BUTTON_WIDTH 150
#define BUTTON_GAP 100

#define BULLET_SIZE 15
#define BULLET_SPEED  20
#define BULLET_MISS_MODIFIER 10

typedef enum {
    QUIT,
    MENU,
    INTRO_1,
    INTRO_2,
    LEVEL1_INTRO,
    LEVEL1_CHOOSE,
    LEVEL1,
    LEVEL2_INTRO,
    LEVEL2_CHOOSE,
    LEVEL2,
    LEVEL3_INTRO,
    LEVEL3_CHOOSE,
    LEVEL3,
    LEVEL_SECRET_INTRO,
    LEVEL_SECRET,
    OUTRO,
} SCENE;

enum BUTTON_TYPE_MENU {
    START_BUTTON,
    FIRST_LEVEL_BUTTON,
    SECOND_LEVEL_BUTTON,
    THIRD_LEVEL_BUTTON,
    EXIT_BUTTON,
};

SDL_Rect Rect_new(int x, int y, int w, int h);

#endif
