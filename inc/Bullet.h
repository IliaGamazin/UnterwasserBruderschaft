#ifndef BULLET_H
#define BULLET_H

#include "./Libs.h"
#include "./Vector.h"
#include "./Rgba.h"
#include "./Tilemap.h"

typedef struct {
    Vector2 position;
    Vector2 direction;
    Rgba color;
} Bullet;

Bullet Bullet_new(Vector2 position, Vector2 direction, uint32_t velocity, Rgba color);
void Bullet_update(Bullet *bullet);
void Bullet_render(SDL_Renderer *renderer, Bullet bullet, Tilemap *map);

#endif

