#include <math.h>

#include "./Entity.h"

// Entity

void Entity_destroy(Entity *entity) {
    Weapon_destroy(entity -> weapon);
    SDL_DestroyTexture(entity -> texture);
    free(entity);
}

void Entity_render(SDL_Renderer *renderer, Entity *entity) {
    SDL_Rect src_rect = (SDL_Rect) {
        (entity -> current_frame * entity -> rect.w) + entity -> current_frame,
        0,
        entity -> rect.w,
        entity -> rect.h,
    };

    double angle = (entity -> direction.x < 0 ? 180 : 0) + radians_to_degrees(atan(entity -> direction.y / entity -> direction.x));

    SDL_RenderCopyEx(
        renderer,
        entity -> texture,
        &src_rect,
        &entity -> rect,
        angle,
        NULL,
        SDL_FLIP_NONE
    );
}

// Entity player

Entity *Player_new(
    SDL_Renderer *renderer,
    CHARACTER_TYPE type,
    SDL_Rect rect,
    Vector2 direction,
    double speed,
    uint32_t animation_speed
) {
    Entity *entity = malloc(sizeof(Entity));

    entity -> rect = rect;
    entity -> direction = direction;
    entity -> speed = speed;
    entity -> last_animated = 0;
    entity -> animation_speed = animation_speed;
    entity -> current_frame = 0;

    switch (type) {
        case SHAYLUSHAY:
            entity -> texture = IMG_LoadTexture(renderer, "./media/img/shaylushay.png");
            entity -> weapon = Weapon_new(RIFLE);
            break;
        case YALTPILS:
            entity -> texture = IMG_LoadTexture(renderer, "./media/img/yaltpils.png");
            entity -> weapon = Weapon_new(PISTOL);
            break;
        case DAWAWUE:
            entity -> texture = IMG_LoadTexture(renderer, "./media/img/dawawue.png");
            entity -> weapon = Weapon_new(SHOTGUN);
            break;
    }

    return entity;
}

void Player_update(Entity *entity) {
    Vector2 direction = Vector2_new(0, 0);

    const uint8_t *keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_W]) {
        direction = Vector2_add(
            direction,
            Vector2_new(0, -1)
        );
    }

    if (keys[SDL_SCANCODE_S]) {
        direction = Vector2_add(
            direction,
            Vector2_new(0, 1)
        );
    }

    if (keys[SDL_SCANCODE_A]) {
        direction = Vector2_add(
            direction,
            Vector2_new(-1, 0)
        );
    }

    if (keys[SDL_SCANCODE_D]) {
        direction = Vector2_add(
            direction,
            Vector2_new(1, 0)
        );
    }

    Vector2_set_magnitude(&direction, entity -> speed);

    entity -> rect.x += direction.x;
    entity -> rect.y += direction.y;

    if (Vector2_is_null(direction)) {
        return;
    }

    // Handle animation

    if (SDL_GetTicks() > entity -> last_animated + entity -> animation_speed) {
        entity -> current_frame = (entity -> current_frame + 1) % 3;
        entity -> last_animated = SDL_GetTicks();
    }

    // Handle collision
}

// Entity enemy


