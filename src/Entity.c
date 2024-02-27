#include "../inc/Entity.h"

// Entity

void Entity_destroy(Entity *entity) {
    Weapon_destroy(entity->weapon);
    SDL_DestroyTexture(entity->texture);
    free(entity);
}

void Entity_render(SDL_Renderer *renderer, Entity *entity, Tilemap *map) {
    SDL_Rect src_rect = {
        entity->current_frame * entity->rect.w,
        0,
        entity->rect.w,
        entity->rect.h,
    };

    double angle = radians_to_degrees(atan2(entity->direction.y, entity->direction.x));
  
    SDL_SetRenderTarget(renderer, map->render_texture);
    SDL_RenderCopyEx(
        renderer,
        entity->texture,
        &src_rect,
        &entity->rect,
        angle,
        &entity->pivot,
        SDL_FLIP_NONE
    );
    SDL_SetRenderTarget(renderer, NULL);
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

    entity->rect = rect;
    entity->hitbox = (SDL_Rect) {
        3, // Offset on x
        0, // Offset on y
        49,
        49,
    };
    entity->pivot = (SDL_Point) {
        entity->hitbox.w / 2 + entity->hitbox.x,
        entity->hitbox.h / 2 + entity->hitbox.y
    };
    entity->direction = direction;
    entity->speed = speed;
    entity->last_animated = 0;
    entity->animation_speed = animation_speed;
    entity->current_frame = 0;

    switch (type) {
        case SHAYLUSHAY:
            entity->texture = IMG_LoadTexture(renderer, "./resource/img/entities/shaylushay.png");
            entity->weapon = Weapon_new(RIFLE);
            break;
        case YALTPILS:
            entity->texture = IMG_LoadTexture(renderer, "./resource/img/entities/yaltpils.png");
            entity->weapon = Weapon_new(PISTOL);
            break;
        case DAWAWUE:
            entity->texture = IMG_LoadTexture(renderer, "./resource/img/entities/dawawue.png");
            entity->weapon = Weapon_new(SHOTGUN);
            break;
    }

    return entity;
}

void Player_update(Entity *entity, Tilemap *map, SDL_Rect *viewport) {
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

    // Return if no movement detected

    if (Vector2_is_null(direction)) {
        return;
    }

    // Hitbox literal

    SDL_Rect hitbox_literal = Rect_new(
        entity->rect.x + entity->hitbox.x,
        entity->rect.y + entity->hitbox.y,
        entity->hitbox.w,
        entity->hitbox.h
    );

    // Calculate hit distance

    double hit_distance = INFINITY;

    if (direction.x) {
        Ray ray = Ray_new(
            Vector2_new(
                hitbox_literal.x + hitbox_literal.w * (direction.x > 0),
                hitbox_literal.y
            ),
            direction
        );

        while (ray.origin.y <= hitbox_literal.y + hitbox_literal.h) {
            double cast = Map_raycast(map, ray, WALL | OBSTACLE);

            if (!cast) {
                return;
            }

            if (cast < hit_distance) {
                hit_distance = cast;
            }

            ray.origin.y++;
        }
    }

    if (direction.y) {
        Ray ray = Ray_new(
            Vector2_new(
                hitbox_literal.x,
                hitbox_literal.y + hitbox_literal.h * (direction.y > 0)
            ),
            direction
        );

        while (ray.origin.x <= hitbox_literal.x + hitbox_literal.w) {
            double cast = Map_raycast(map, ray, WALL | OBSTACLE);

            if (!cast) {
                return;
            }

            if (cast < hit_distance) {
                hit_distance = cast;
            }

            ray.origin.x++;
        }
    }

    // Tweak walk distance

    Vector2_set_magnitude(&direction, (hit_distance < entity->speed ? hit_distance : entity->speed));

    // Move viewport

    Viewport_centralize(viewport, entity->rect.x + entity->pivot.x, entity->rect.y + entity->pivot.y);

    if (viewport->x < 0) {
        viewport->x = 0;
    } else if (viewport->x + viewport->w >= (int) map->width * TILE_SIZE) {
        viewport->x = map->width * TILE_SIZE - viewport->w - 1;
    }

    if (viewport->y < 0) {
        viewport->y = 0;
    } else if (viewport->y + viewport->h >= (int) map->height * TILE_SIZE) {
        viewport->y = map->height * TILE_SIZE - viewport->h - 1;
    }

    // Move player

    entity->rect.x += direction.x;
    entity->rect.y += direction.y;

    // Animate player

    if (SDL_GetTicks() > entity->last_animated + entity->animation_speed) {
        entity->current_frame = (entity->current_frame + 1) % 3;
        entity->last_animated = SDL_GetTicks();
    }

    // Handle collision
}

// Entity enemy

