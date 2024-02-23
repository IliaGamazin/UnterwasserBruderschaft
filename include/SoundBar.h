#pragma once
#ifndef SOUNDBAR_H
#define SOUNDBAR_H

#include "./Libs.h"

typedef struct {
    SDL_Rect rect;
    SDL_Texture *texture;
} SoundBar;

SoundBar *SoundBar_new(SDL_Renderer *renderer, int x, int y, int w, int h);
void SoundBar_destroy(SoundBar *bar);
void SoundBar_update(SoundBar *bar, int volume);

#endif

