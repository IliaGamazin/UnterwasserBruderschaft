#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include "./Bullet.h"

typedef struct {
    Bullet *bullets;
    size_t capacity;
    size_t count;
} BulletManager;

BulletManager *BulletManager_new(size_t capacity);
void BulletManager_destroy(BulletManager *manager);
void BulletManager_remove(BulletManager *manager, size_t index);
void BulletManager_add(BulletManager *manager, Bullet bullet);
void BulletManager_update(BulletManager *manager, int levelWidth, int levelHeight);
void BulletManager_render(SDL_Renderer *renderer, BulletManager *manager, Tilemap *map);

#endif

