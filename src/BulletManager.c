#include "./BulletManager.h"

// BulletManager

BulletManager *BulletManager_new(size_t capacity) {
    BulletManager *manager = malloc(sizeof(BulletManager));
    
    manager -> bullets = malloc(sizeof(Bullet) * capacity);
    manager -> capacity = capacity;
    manager -> count = 0;

    return manager;
}

void BulletManager_destroy(BulletManager *manager) {
    free(manager -> bullets);
    free(manager);
}

void BulletManager_remove(BulletManager *manager, size_t index) {
    if (index < manager -> count - 1) {
        manager -> bullets[index] = manager -> bullets[manager -> count - 1];
    }

    manager -> count--;
}

void BulletManager_add(BulletManager *manager, Bullet bullet) {
    manager -> bullets[manager -> count++] = bullet;
}

void BulletManager_update(BulletManager *manager) {
    for (size_t i = 0; i < manager -> count; i++) {
        Bullet_update(&manager -> bullets[i]);

        if (manager -> bullets[i].position.x < 0 || manager -> bullets[i].position.x >= 1280 ||
            manager -> bullets[i].position.y < 0 || manager -> bullets[i].position.y >= 720) {
            BulletManager_remove(manager, i);
            i--;
        }
    }
}

void BulletManager_render(SDL_Renderer *renderer, BulletManager *manager) {
    for (size_t i = 0; i < manager -> count; i++) {
        Bullet_render(renderer, manager -> bullets[i]);
    }
}

