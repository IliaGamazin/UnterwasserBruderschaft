#include "./BulletManager.h"

// BulletManager

BulletManager *BulletManager_new(size_t capacity) {
    BulletManager *manager = malloc(sizeof(BulletManager));
    
    manager->bullets = malloc(sizeof(Bullet) * capacity);
    manager->capacity = capacity;
    manager->count = 0;

    return manager;
}

void BulletManager_destroy(BulletManager *manager) {
    free(manager->bullets);
    free(manager);
}

void BulletManager_remove(BulletManager *manager, size_t index) {
    if (index < --manager->count) {
        manager->bullets[index] = manager->bullets[manager->count];
    }
}

void BulletManager_add(BulletManager *manager, Vector2 position, Vector2 direction, uint32_t velocity, Rgba color) {
    if (manager->count < manager->capacity) {
        // Проверка наличия свободного места в массиве пуль
        Vector2 normalizedDirection = direction;
        Vector2_normalize(&normalizedDirection);
        Bullet bullet = Bullet_new(position, normalizedDirection, velocity, color);
        manager->bullets[manager->count++] = bullet;
    }
}

void BulletManager_update(BulletManager *manager) {
    for (size_t i = 0; i < manager->count; i++) {
        if (manager->bullets[i].position.x < 0 || manager->bullets[i].position.x >= 1280 ||
            manager->bullets[i].position.y < 0 || manager->bullets[i].position.y >= 720) {
            BulletManager_remove(manager, i--);
            continue;
        }

        Bullet_update(&manager->bullets[i]);
    }
}

void BulletManager_render(SDL_Renderer *renderer, BulletManager *manager) {
    for (size_t i = 0; i < manager->count; i++) {
        Bullet_render(renderer, manager->bullets[i]);
    }
}