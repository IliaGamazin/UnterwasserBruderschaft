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
#include <stdio.h>
#include <math.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define BUTTON_COUNT_MENU 5
#define BUTTON_COUNT_CHOOSE 3
#define BUTTON_HEIGHT 60
#define BUTTON_WIDTH 150
#define BUTTON_GAP 100

#define BULLET_SIZE 15
#define BULLET_SPEED  20
#define BULLET_MISS_MODIFIER 10
#define MAX_VOLUME 120
#define CURRENT_LEVEL_INTRO level-2 
#define CURRENT_LEVEL_CHOOSE level-1

#define TILE_SIZE 40
#define TILES_COUNT ((WINDOW_WIDTH*WINDOW_HEIGHT)/(TILE_SIZE*TILE_SIZE))
#define TILES_TEXTURE_COUNT 4

enum TILE_TYPE{
    WALL_HORIZONTAL,
    WALL_VERTICAL,
    FLOOR_WOOD,
    FLOOR_MARBLE
};

typedef enum {
    MENU,
    INTRO,
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
    OUTRO
}SCENE;

enum BUTTON_TYPE_MENU {
    START_BUTTON,
    FIRST_LEVEL_BUTTON,
    SECOND_LEVEL_BUTTON,
    THIRD_LEVEL_BUTTON,
    EXIT_BUTTON
};

typedef enum{
    SHAYLUSHAY,
    YALTPILS,
    DAWAWUE
}CHARACTER_TYPE;

typedef enum {
    RIFLE,
    PISTOL,
    SHOTGUN
}WEAPON_TYPE;

SDL_Rect createRect(int x, int y, int rectWidth, int rectHeight);

#endif