// Camera.h
#ifndef CAMERA_H
#define CAMERA_H
#include <SDL2/SDL_rect.h>
#include "Vector.h" 

typedef struct {
    SDL_Rect viewPort;
    Vector2 position;
} Camera;

#endif





