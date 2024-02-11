#pragma once

#include "Libs.h"
#include "Entity.h"

#ifndef PLAYER_DRIVE_H
#define PLAYER_DRIVE_H

#define PLAYER_WIDTH 212
#define PLAYER_HEIGHT 94

#define TOP_BORDER_HEIGHT_RATIO 0.2
#define BOTTOM_BORDER_HEIGHT_RATIO 0.22

typedef struct {
    SDL_Rect rect;
    SDL_Texture *texture;
    int velocity_x;
    int velocity_y;
    CHARACTER_TYPE type;
} Player;

Player *player_drive_new(SDL_Renderer *r, int x, int y, CHARACTER_TYPE type);

void player_drive_update(Player *player_drive, bool key_w, bool key_s);

void player_drive_render(Player *player_drive, SDL_Renderer *r);

void player_drive_destroy(Player *player_drive);

#endif

