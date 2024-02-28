#ifndef ENTITY_H
#define ENTITY_H

#include <math.h>

#include "./Libs.h"
#include "./Vector.h"
#include "./Weapon.h"
#include "./Viewport.h"
#include "./Tilemap.h"

// CHARACTER_TYPE

typedef enum {
    SHAYLUSHAY,
    YALTPILS,
    DAWAWUE,
} CHARACTER_TYPE;

// Entity

typedef struct {
    SDL_Rect rect;
    SDL_Rect hitbox;
    SDL_Point pivot;
    Vector2 direction;
    double speed;
    Weapon *weapon;
    SDL_Texture *texture;
    uint32_t last_animated;
    uint32_t animation_speed;
    uint32_t current_frame;
    Mix_Chunk *walking_sound;
} Entity;

void Entity_destroy(Entity *entity);
void Entity_render(SDL_Renderer *renderer, Entity *entity, Tilemap *map);

// Entity player

Entity *Player_new(
    SDL_Renderer *renderer,
    CHARACTER_TYPE type,
    SDL_Rect rect,
    Vector2 direction,
    double speed,
    uint32_t animation_speed
);
void Player_update(Entity *entity, Tilemap *map, Viewport *viewport, Vector2 mouse_position);

#endif

