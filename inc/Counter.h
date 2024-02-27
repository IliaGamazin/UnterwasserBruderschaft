#pragma once
#ifndef COUNTER_H
#define COUNTER_H

#include "Libs.h"

#define COUNTER_SIZE 50
#define HPCOUNTER_WIDTH 121
#define HPCOUNTER_HEIGHT 40

typedef struct
{
    SDL_Rect HPcounterRect;
    SDL_Rect HPcounterClip;

    SDL_Rect UnitsRect;
    SDL_Rect TensRect;

    SDL_Rect UnitsClip;
    SDL_Rect TensClip;

    SDL_Texture* HPCounterTexture;

    SDL_Texture* UnitsTexture;
    SDL_Texture* TensTexture;

    int countnumber;
    int countHP;

} Counter;

Counter* Counter_create(SDL_Renderer* gRenderer);

void CounterSprites(Counter *counter);
void Counter_destroy(Counter  *counter);
void Counter_show(Counter *counter, SDL_Renderer* gRenderer);

#endif
