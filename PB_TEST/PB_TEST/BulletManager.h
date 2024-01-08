#pragma once
#include "Bullet.h"
#include "Entity.h"
#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

typedef struct {
    Bullet** bullets;
    int capacity;
    int count;
}BulletManager;

BulletManager* createBulletManager(int capacity);
void destroyBulletManager(BulletManager* bulletManager);
void destroyCollidedBullet(BulletManager* bulletManager, int index);
void showAllBullets(SDL_Renderer* r, BulletManager* bulletManager);
void shoot(BulletManager* bulletManager, Entity* Shooter, SDL_Renderer* r);
void spawnBullet(BulletManager* bulletManager, Entity* Shooter, SDL_Renderer* r);
void updateBulletManager(BulletManager* bulletManager);

#endif