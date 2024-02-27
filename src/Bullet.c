#include "../inc/Bullet.h"

// Bullet

Bullet Bullet_new(Vector2 position, Vector2 direction, uint32_t velocity, Rgba color) {
    Vector2_set_magnitude(&direction, velocity);

    return (Bullet) {
        position,
        direction,
        color,
    };
}

void Bullet_update(Bullet *bullet) {
    bullet->position = Vector2_add(bullet->position, bullet->direction);
}

void Bullet_render(SDL_Renderer *renderer, Bullet bullet, Tilemap *map) {
    Vector2 start = Vector2_sub(bullet.position, bullet.direction);

    SDL_SetRenderTarget(renderer, map->render_texture);
    SDL_SetRenderDrawColor(
        renderer,
        bullet.color.r,
        bullet.color.g,
        bullet.color.b,
        bullet.color.a
    );
    SDL_RenderDrawLine(
        renderer,
        start.x,
        start.y,
        bullet.position.x,
        bullet.position.y
    );
    SDL_SetRenderTarget(renderer, NULL);
}

