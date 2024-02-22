#pragma once
#ifndef AMMOBOX_H
#define AMMOBOX_H

#include "Camera.h"
#include "./Libs.h"
#include "./Tilemap.h"

typedef struct AmmoBox AmmoBox;
struct AmmoBox {
    SDL_Rect rect;
    SDL_Texture *full_tex;
    SDL_Texture *empty_tex;
    Mix_Chunk *reload_sound;
    bool is_full;
};

AmmoBox AmmoBox_new(SDL_Renderer *r, int x, int y);
void AmmoBox_render(SDL_Renderer *r, AmmoBox box, Camera camera);
void AmmoBox_destroy(AmmoBox box);

#endif

