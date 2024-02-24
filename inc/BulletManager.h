#pragma once
#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H
#include "Camera.h"
#include "./Bullet.h"

typedef struct BulletManager BulletManager;
struct BulletManager {
    Bullet *bullets;
    size_t capacity;
    size_t count;
};

BulletManager *BulletManager_new(size_t capacity);
void BulletManager_destroy(BulletManager *manager);
void BulletManager_remove(BulletManager *manager, size_t index);
void BulletManager_add(BulletManager *manager, Bullet bullet);
void BulletManager_update(BulletManager *manager, int levelWidth, int levelHeight);
void BulletManager_render(SDL_Renderer *renderer, BulletManager *manager, Camera camera);

#endif

