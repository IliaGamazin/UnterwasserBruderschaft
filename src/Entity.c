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
    double hit_x_distance = INFINITY;
    double hit_y_distance = INFINITY;

    if (walk_direction.x) {
        Ray ray = Ray_new(
            Vector2_new(
                hitbox_literal.x + hitbox_literal.w * (walk_direction.x > 0),
                hitbox_literal.y
            ),
            walk_direction
        );

        while (ray.origin.y <= hitbox_literal.y + hitbox_literal.h) {
            double hit = Map_raycast(map, ray, WALL | OBSTACLE);
            double hitx = Map_raycast(map, Ray_new(ray.origin, Vector2_new(ray.direction.x, 0)), WALL | OBSTACLE);

            if (hit < hit_distance) {
                hit_distance = hit;
            }

            if (hitx < hit_x_distance) {
                hit_x_distance = hitx;
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
            double hit = Map_raycast(map, ray, WALL | OBSTACLE);
            double hity = Map_raycast(map, Ray_new(ray.origin, Vector2_new(0, ray.direction.y)), WALL | OBSTACLE);

            if (hit < hit_distance) {
                hit_distance = hit;
            }

            if (hity < hit_y_distance) {
                hit_y_distance = hity;
            }

            ray.origin.x++;
        }
    }

    if (!hit_distance && walk_direction.x && walk_direction.y) {
        if (hit_x_distance) {
            walk_direction.y = 0;
            hit_distance = hit_x_distance;
        } else if (hit_y_distance) {
            walk_direction.x = 0;
            hit_distance = hit_y_distance;
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

// Enemy

Entity *Enemy_new(
    SDL_Renderer *renderer,
    ENEMY_TYPE type, //now incl en typ
    SDL_Rect rect,
    Vector2 direction,
    double speed,
    uint32_t animation_speed
) {
    Entity *enemy = malloc(sizeof(Entity));
    if (enemy == NULL) return NULL;
    
    // init obl of ent

    enemy->rect = rect;
    enemy->direction = direction;
    enemy->speed = speed;
    enemy->pivot = (SDL_Point) {
        enemy->rect.w / 2,
        enemy->rect.h / 2,
    };
    enemy->animation_speed = animation_speed;
    enemy->last_animated = 0;
    enemy->current_frame = 0;

    // Swstatement to handle different entypes

    switch (type) {
        case ENEMY_TYPE1:
            enemy->texture = IMG_LoadTexture(renderer, "./resource/img/entities/enemy2.png");
            enemy->weapon = Weapon_new(SHOTGUN);
            enemy->rect.w = 60;
            enemy->rect.h = 50;
            break;
        case ENEMY_TYPE2:
            enemy->texture = IMG_LoadTexture(renderer, "./resource/img/entities/enemy1.png");
            enemy->weapon = Weapon_new(RIFLE);
            enemy->rect.w = 60;
            enemy->rect.h = 44;
            break;
        case ENEMY_TYPE3:
            enemy->texture = IMG_LoadTexture(renderer,  "./resource/img/entities/enemy1.png");
            enemy->weapon = Weapon_new(PISTOL);
            enemy->rect.w = 60;
            enemy->rect.h = 44;
            break;
        default:
            break;
    }

    enemy->hitbox = enemy->rect;

    return enemy;
}

void Enemy_update(Entity *enemy, Entity *player, Tilemap *map, BulletManager *bullet_manager) {
    static uint32_t last_update_time = 0;
    const uint32_t update_interval = 1000;
    static bool is_chasing = false;

    SDL_Rect enemy_hitbox_literal = Rect_new(
        enemy->rect.x + enemy->hitbox.x,
        enemy->rect.y + enemy->hitbox.y,
        enemy->hitbox.w,
        enemy->hitbox.h
    );
    
    Vector2 player_pos = Vector2_new(
        player->rect.x + player->rect.w / 2.0,
        player->rect.y + player->rect.h / 2.0
    );
    Vector2 enemy_pos = Vector2_new(
        enemy->rect.x + enemy->rect.w / 2.0,
        enemy->rect.y + enemy->rect.h / 2.0
    );
    Vector2 enemy_to_player = Vector2_from_points(enemy_pos, player_pos);

    double distance_to_player = Vector2_magnitude(enemy_to_player);
   
    if (!is_chasing) {
        if (SDL_GetTicks() - last_update_time > update_interval) {
            int dir = rand() % 4;
            switch (dir) {
                case 0: enemy->direction = (Vector2){1, 0}; break;
                case 1: enemy->direction = (Vector2){-1, 0}; break;
                case 2: enemy->direction = (Vector2){0, 1}; break;
                case 3: enemy->direction = (Vector2){0, -1}; break;
            }
            last_update_time = SDL_GetTicks();
        }
    }
   
    const float sight_range = 350.0f;

    is_chasing = (distance_to_player <= sight_range) && Map_raycast(map, Ray_new(enemy_pos, enemy_to_player), WALL) > distance_to_player;
    
    if (is_chasing) {
        Vector2 walk_direction = enemy_to_player;

        enemy->direction = enemy_to_player;

        double hit_distance = INFINITY;
        double hit_x_distance = INFINITY;
        double hit_y_distance = INFINITY;

        if (walk_direction.x) {
            Ray ray = Ray_new(
                Vector2_new(
                    enemy_hitbox_literal.x + enemy_hitbox_literal.w * (walk_direction.x > 0),
                    enemy_hitbox_literal.y
                ),
                walk_direction
            );

            while (ray.origin.y <= enemy_hitbox_literal.y + enemy_hitbox_literal.h) {
                double hit = Map_raycast(map, ray, WALL | OBSTACLE);
                double hitx = Map_raycast(map, Ray_new(ray.origin, Vector2_new(ray.direction.x, 0)), WALL | OBSTACLE);

                if (hit < hit_distance) {
                    hit_distance = hit;
                }

                if (hitx < hit_x_distance) {
                    hit_x_distance = hitx;
                }

                ray.origin.y++;
            }
        }

        if (walk_direction.y) {
            Ray ray = Ray_new(
                Vector2_new(
                    enemy_hitbox_literal.x,
                    enemy_hitbox_literal.y + enemy_hitbox_literal.h * (walk_direction.y > 0)
                ),
                walk_direction
            );

            while (ray.origin.x <= enemy_hitbox_literal.x + enemy_hitbox_literal.w) {
                double hit = Map_raycast(map, ray, WALL | OBSTACLE);
                double hity = Map_raycast(map, Ray_new(ray.origin, Vector2_new(0, ray.direction.y)), WALL | OBSTACLE);

                if (hit < hit_distance) {
                    hit_distance = hit;
                }

                if (hity < hit_y_distance) {
                    hit_y_distance = hity;
                }

                ray.origin.x++;
            }
        }

        if (!hit_distance && walk_direction.x && walk_direction.y) {
            if (hit_x_distance) {
                walk_direction.y = 0;
                hit_distance = hit_x_distance;
            } else if (hit_y_distance) {
                walk_direction.x = 0;
                hit_distance = hit_y_distance;
            }
        }

        // Tweak walk distance

        Vector2_set_magnitude(&walk_direction, (hit_distance < enemy->speed ? hit_distance : enemy->speed));

        // Walking Sound 
        
        if (!Mix_Playing(3)) {
            Mix_PlayChannel(3, enemy->walking_sound, 1);
        }

        // Animate enemy

        if (SDL_GetTicks() > enemy->last_animated + enemy->animation_speed) {
            enemy->current_frame = (enemy->current_frame + 1) % 3;
            enemy->last_animated = SDL_GetTicks();
        }

        // Move enemy
        
        enemy->rect.x += round(walk_direction.x);
        enemy->rect.y += round(walk_direction.y);
        
        if (enemy->weapon && distance_to_player < sight_range) {
            Weapon_shoot(enemy->weapon, bullet_manager, enemy_pos, enemy->direction);
            enemy->weapon->ammo++;
        }
    }
}

// EnemyManager

EnemyManager *EnemyManager_new(SDL_Renderer *r, int capacity, int count) {
    EnemyManager *manager = malloc(sizeof(EnemyManager));

    manager->enemies = malloc(sizeof(Entity) * capacity);
    manager->capacity = capacity;
    manager->enemy_count = count;
    
    manager->enemies[0] = Enemy_new(r, ENEMY_TYPE1, Rect_new(100, 100, 70, 49), Vector2_new(0, 0), 3, 500);
    manager->enemies[1] = Enemy_new(r, ENEMY_TYPE2, Rect_new(250, 250, 70, 49), Vector2_new(0, 0), 3, 500);
    manager->enemies[2] = Enemy_new(r, ENEMY_TYPE3, Rect_new(300, 300, 70, 49), Vector2_new(0, 0), 3, 500);
    
    return manager; 
}

void EnemyManager_update(EnemyManager *manager, Entity *player, Tilemap *map, BulletManager* bullet_manager) {
    for (size_t i = 0; i < manager->enemy_count; i++) {
        Enemy_update(manager->enemies[i], player, map, bullet_manager);
    }
}

void EnemyManager_render(EnemyManager *manager, SDL_Renderer *renderer, Tilemap *map) {
    for (size_t i = 0; i < manager->enemy_count; i++) {
        Entity_render(renderer, manager->enemies[i], map);
    }
}

void EnemyManager_destroy(EnemyManager *manager) {
    for (size_t i = 0; i < manager->enemy_count; i++) {
        Entity_destroy(manager->enemies[i]);
        manager->enemies[i] = NULL;
    }
    manager->enemy_count = 0;
    free(manager->enemies);
    free(manager);
}

