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

typedef enum {
    SHOTGUNNER,
    PISTOLER,
} ENEMY_TYPE;

// Entity

typedef struct {
    SDL_Rect rect;
    SDL_Rect hitbox;
    SDL_Point pivot;
    Vector2 direction;
    double speed;
    bool is_dead;
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

// Entity enemy

Entity *Enemy_new(
    SDL_Renderer *renderer,
    ENEMY_TYPE type,
    SDL_Rect rect,
    Vector2 direction,
    double speed,
    uint32_t animation_speed
);
void Enemy_update(Entity *enemy, Entity *player, Tilemap *map, BulletManager *bullet_manager);

// EnemyManager

typedef struct {
    Entity **enemies;
    size_t enemy_count;
    size_t capacity;
} EnemyManager;

EnemyManager *EnemyManager_new(Entity **enemies, int capacity, int count);

void EnemyManager_update(EnemyManager *manager, Entity *player, Tilemap *map, BulletManager* bullet_manager);
void EnemyManager_render(EnemyManager *manager, SDL_Renderer *renderer, Tilemap *map);
void EnemyManager_destroy(EnemyManager *manager);

#endif

