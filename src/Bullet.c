#include "../include/Bullet.h"
#include "../include/Camera.h"

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

void Bullet_render(SDL_Renderer *renderer, Bullet bullet, Camera camera) {
    // Adjusting bullet position
    Vector2 adjustedStart = Vector2_sub(bullet.position, bullet.direction);
    Vector2 adjustedEnd = bullet.position;

    // Subtracted the camera position to get the correct screen coordinates for bullets
    adjustedStart.x -= camera.position.x;
    adjustedStart.y -= camera.position.y;
    adjustedEnd.x -= camera.position.x;
    adjustedEnd.y -= camera.position.y;

    SDL_SetRenderDrawColor(
        renderer,
        bullet.color.r,
        bullet.color.g,
        bullet.color.b,
        bullet.color.a
    );
    SDL_RenderDrawLine(
        renderer,
        adjustedStart.x,
        adjustedStart.y,
        adjustedEnd.x,
        adjustedEnd.y
    );
}

