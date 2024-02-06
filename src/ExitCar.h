#pragma once
#ifndef EXITCAR_H
#define EXITCAR_H

#include "./Libs.h"
#include "./Entity.h"
#include "Camera.h"// ExitCar

typedef struct {
    SDL_Rect car_rect;
    SDL_Rect door_rect;
    SDL_Rect door_collider;
    SDL_Rect seat_collider;
    SDL_Texture *car_tex;
    SDL_Texture *door_tex;
    double door_angle;
    bool is_opened;
    bool is_playing_sound;
    Mix_Chunk *open_sound;
} ExitCar;

ExitCar *ExitCar_new(SDL_Renderer *r);
void ExitCar_render(SDL_Renderer *r, ExitCar *Car, Camera camera);
void ExitCar_update(ExitCar *Car, SDL_Point PlayerCenter);
void ExitCar_destroy(ExitCar *Car);

#endif

