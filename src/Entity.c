#include "../inc/Entity.h"

int clampi(int x, int min, int max) {
    if (x < min) {
        return min;
    }

    if (x > max) {
        return max;
    }

    return x;
}

// Entity

void Entity_destroy(Entity *entity) {
    Weapon_destroy(entity->weapon);
    SDL_DestroyTexture(entity->texture);
    Mix_FreeChunk(entity->walking_sound);
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
    entity->walking_sound = Mix_LoadWAV("./resource/sound/walking_sound.wav");

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

void Player_update(Entity *entity, Tilemap *map, SDL_Rect *viewport, Vector2 mouse_position) {
    // Calculate player center

    Vector2 player_center = Vector2_new(
        entity->rect.x + entity->pivot.x,
        entity->rect.y + entity->pivot.y
    );

    // Calculate map pixel size
    
    Vector2 map_pixel_size = Vector2_new(
        map->width * TILE_SIZE,
        map->height * TILE_SIZE
    );

    // Calculate walk_direction

    Vector2 walk_direction = Vector2_new(0, 0);

    const uint8_t *keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_W]) {
        walk_direction = Vector2_add(
            walk_direction,
            Vector2_new(0, -1)
        );
    }

    if (keys[SDL_SCANCODE_S]) {
        walk_direction = Vector2_add(
            walk_direction,
            Vector2_new(0, 1)
        );
    }

    if (keys[SDL_SCANCODE_A]) {
        walk_direction = Vector2_add(
            walk_direction,
            Vector2_new(-1, 0)
        );
    }

    if (keys[SDL_SCANCODE_D]) {
        walk_direction = Vector2_add(
            walk_direction,
            Vector2_new(1, 0)
        );
    }

    // Update direction

    entity->direction = Vector2_from_points(
        player_center,
        Vector2_new(
            mouse_position.x + viewport->x,
            mouse_position.y + viewport->y
        )
    );

    // Hitbox literal

    SDL_Rect hitbox_literal = Rect_new(
        entity->rect.x + entity->hitbox.x,
        entity->rect.y + entity->hitbox.y,
        entity->hitbox.w,
        entity->hitbox.h
    );

    // Update viewport

    if (keys[SDL_SCANCODE_LSHIFT]) {
        Viewport_centralize(
            viewport,
            player_center.x + mouse_position.x - viewport->w / 2,
            player_center.y + mouse_position.y - viewport->h / 2
        );
    } else {
        Viewport_centralize(viewport, player_center.x, player_center.y);
    }

    viewport->x = clampi(viewport->x, 0, map_pixel_size.x - viewport->w - 1);
    viewport->y = clampi(viewport->y, 0, map_pixel_size.y - viewport->h - 1);

    // Return if no movement detected

    if (Vector2_is_null(walk_direction)) {
        return;
    }

    // Calculate hit distance

    double hit_distance = INFINITY;

    if (walk_direction.x) {
        Ray ray = Ray_new(
            Vector2_new(
                hitbox_literal.x + hitbox_literal.w * (walk_direction.x > 0),
                hitbox_literal.y
            ),
            walk_direction
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

    if (walk_direction.y) {
        Ray ray = Ray_new(
            Vector2_new(
                hitbox_literal.x,
                hitbox_literal.y + hitbox_literal.h * (walk_direction.y > 0)
            ),
            walk_direction
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

    Vector2_set_magnitude(&walk_direction, (hit_distance < entity->speed ? hit_distance : entity->speed));

    // Walking Sound 
    
    if (!Mix_Playing(3)) {
        Mix_PlayChannel(3, entity->walking_sound, 1);
    }

    // Move player

    entity->rect.x += round(walk_direction.x);
    entity->rect.y += round(walk_direction.y);

    // Animate player

    if (SDL_GetTicks() > entity->last_animated + entity->animation_speed) {
        entity->current_frame = (entity->current_frame + 1) % 3;
        entity->last_animated = SDL_GetTicks();
    }
}

// Entity enemy

