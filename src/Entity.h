#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "./Libs.h"
#include "./Vector.h"
#include "./Weapon.h"

// CHARACTER_TYPE

typedef enum CHARACTER_TYPE CHARACTER_TYPE;
enum CHARACTER_TYPE {
    SHAYLUSHAY,
    YALTPILS,
    DAWAWUE,
};

// Entity

typedef struct Entity Entity;
struct Entity {
    SDL_Rect rect;
    Vector2 direction;
    double speed;
    Weapon *weapon;
    SDL_Texture *texture;
    uint32_t last_animated;
    uint32_t animation_speed;
    uint32_t current_frame;
};

void Entity_destroy(Entity *entity);
void Entity_render(SDL_Renderer *renderer, Entity *entity);

// Entity player

Entity *Player_new(
    SDL_Renderer *renderer,
    CHARACTER_TYPE type,
    SDL_Rect rect,
    Vector2 direction,
    double speed,
    uint32_t animation_speed
);
void Player_update(Entity *entity);

#endif

