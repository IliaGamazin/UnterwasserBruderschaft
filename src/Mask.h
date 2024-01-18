#pragma once
#ifndef MASK_H
#define MASK_H

#include "./Libs.h"
#include "./Entity.h"

typedef struct Mask Mask;
struct Mask {
    SDL_Rect maskRect;
    SDL_Texture* maskTextureIdle;
    SDL_Texture* maskTextureActive;
    bool isAnimated;
    double angle;
};

Mask* createMask(SDL_Renderer* r, CHARACTER_TYPE type, int x, int y, int w, int h);
Mask** fillMaskArr(SDL_Renderer* r);
void animMask(SDL_Renderer* r, Mask* m);
void destroyMask(Mask* m);
#endif
