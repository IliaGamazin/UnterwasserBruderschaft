#pragma once
#include "Libs.h"
#include "Entity.h"
#ifndef EXITCAR_H
#define EXITCAR_H

typedef struct{
    SDL_Rect carRect;
    SDL_Rect doorRect;
    SDL_Rect doorCollider;
    SDL_Rect seatCollider;
    SDL_Texture* carTex;
    SDL_Texture* doorTex;
    double doorAngle;
    bool isOpened;
    bool isPlayingSound;
    Mix_Chunk* openSound;
}ExitCar;

ExitCar* ExitCar_new(SDL_Renderer* r);
void ExitCar_render(SDL_Renderer* r, ExitCar* Car);
void ExitCar_update(ExitCar* Car, SDL_Point PlayerCenter);
void ExitCar_destroy(ExitCar* Car);

#endif