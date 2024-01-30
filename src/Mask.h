#pragma once
#ifndef MASK_H
#define MASK_H

#include "./Libs.h"
#include "./Entity.h"

typedef struct Mask Mask;
struct Mask {
    SDL_Rect mask_rect;
    SDL_Texture *mask_tex_idle;
    SDL_Texture *mask_tex_active;
    int init_y;
    bool is_animated;
    double angle;
};

Mask *Mask_new(SDL_Renderer *r, CHARACTER_TYPE type, int x, int y, int w, int h);
Mask **Mask_arr_new(SDL_Renderer *r);
void Mask_render(SDL_Renderer *r, Mask* m);
void Mask_destroy(Mask *m);
#endif
