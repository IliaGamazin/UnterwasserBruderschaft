#pragma once
#ifndef PLANE_H
#define PLANE_H

#include "Libs.h"

#define PLANE_WIDTH 150
#define PLANE_HEIGHT 80
#define PLANE_VEL 7

typedef struct
{
    int pVelX;
    SDL_Rect PlaneRect;
    SDL_Rect PlaneClip;
    SDL_Texture* Plane;
    int frame;
    Mix_Chunk* PlaneSound;
}Enemy;

Enemy* Plane_create(SDL_Renderer* gRenderer);

void Plane_move(Enemy *plane);
void Plane_destroy(Enemy *plane);
void Plane_show(Enemy *plane, SDL_Renderer* gRenderer);

#endif
