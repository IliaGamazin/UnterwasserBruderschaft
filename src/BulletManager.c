#include "BulletManager.h"

BulletManager* createBulletManager(int capacity) {
    BulletManager* bulletManager = (BulletManager*)malloc(sizeof(BulletManager));
    bulletManager->bullets = (Bullet**)malloc(capacity * sizeof(Bullet*));
    bulletManager->capacity = capacity;
    bulletManager->count = 0;
    return bulletManager;
}
void destroyBulletManager(BulletManager* bulletManager) {
    for (int i = 0; i < bulletManager->count; ++i) {
        destroyBullet(bulletManager->bullets[i]);
    }
    free(bulletManager->bullets);
    free(bulletManager);
}
void destroyCollidedBullet(BulletManager* bulletManager, int index) {
    destroyBullet(bulletManager->bullets[index]);
    if (index < bulletManager->count - 1) {
        bulletManager->bullets[index] = bulletManager->bullets[bulletManager->count - 1];
    }
    --bulletManager->count;
}
void spawnBullet(BulletManager* bulletManager, Entity* Shooter, SDL_Renderer* r) {
    if (bulletManager->count < bulletManager->capacity) {
        int spawnX = Shooter->entityRect.x + Shooter->entityRect.w / 2 - BULLET_SIZE / 2;
        int spawnY = Shooter->entityRect.y + Shooter->entityRect.h / 2 - BULLET_SIZE / 2;

        Bullet* newBullet = createBullet(spawnX, spawnY, Shooter->angle, r);
        bulletManager->bullets[bulletManager->count++] = newBullet;
    }
}
void updateBulletManager(BulletManager* bulletManager) {
    for (int i = 0; i < bulletManager->count; ++i) {
        updateBullet(bulletManager->bullets[i]);
        if (bulletManager->bullets[i]->bulletRect.x < 0 || bulletManager->bullets[i]->bulletRect.x > 1280 ||
            bulletManager->bullets[i]->bulletRect.y < 0 || bulletManager->bullets[i]->bulletRect.y > 720) {
            destroyCollidedBullet(bulletManager, i);
            --i;
        }
    }
}
void showAllBullets(SDL_Renderer* r, BulletManager* bulletManager) {
    for (int i = 0; i < bulletManager->count; ++i) {
        showBullet(r, bulletManager->bullets[i]);
    }
}
void shoot(BulletManager* bulletManager, Entity* Shooter, SDL_Renderer* r) {
    Mix_PlayChannel(-1, Shooter->entityWeapon.shotSound, 0);
    for (int i = 0; i < Shooter->entityWeapon.bulletsNum; i++)
    {
        spawnBullet(bulletManager, Shooter, r);
    }
    Shooter->entityWeapon.ammoInMag--;
    Shooter->entityWeapon.totalAmmoCount--;
}