#include "../inc/Header_main.h"
#include "../inc/Viewport.h"

void bullet_collider_enemy(BulletManager *bullet_manager, EnemyManager *enemy_manager, Tilemap *map) {
    for (size_t i = 0; i < bullet_manager->count; i++) {
        Vector2 start = Vector2_sub(bullet_manager->bullets[i].position, bullet_manager->bullets[i].direction);
    
        double wall_distance = Map_raycast(
            map,
            Ray_new(start, bullet_manager->bullets[i].direction),
            WALL
        );

        if (wall_distance <= Vector2_magnitude(bullet_manager->bullets[i].direction)) {
            BulletManager_remove(bullet_manager, --i);
            continue;
        }

        for (size_t j = 0; j < enemy_manager->capacity; j++) {
            int start_x = start.x;
            int start_y = start.y;
            int end_x = bullet_manager->bullets[i].position.x;
            int end_y = bullet_manager->bullets[i].position.y;

            if (bullet_manager->bullets[i].is_player && SDL_IntersectRectAndLine(
                &enemy_manager->enemies[j]->rect, 
                &start_x, 
                &start_y, 
                &end_x,
                &end_y)) 
                {
                if (!enemy_manager->enemies[j]->is_dead) {
                    enemy_manager->enemy_count--;
                }
                enemy_manager->enemies[j]->is_dead = true;  
                
                BulletManager_remove(bullet_manager, --i);
            }
        } 
    }
}

void bullet_collider_player(BulletManager *bullet_manager, Entity* player, Tilemap *map) {
    for (size_t i = 0; i < bullet_manager->count; i++) {
        Vector2 start = Vector2_sub(bullet_manager->bullets[i].position, bullet_manager->bullets[i].direction);
    
        double wall_distance = Map_raycast(
            map,
            Ray_new(start, bullet_manager->bullets[i].direction),
            WALL
        );

        if (wall_distance <= Vector2_magnitude(bullet_manager->bullets[i].direction)) {
            BulletManager_remove(bullet_manager, --i);
            continue;
        }

        
        int start_x = start.x;
        int start_y = start.y;
        int end_x = bullet_manager->bullets[i].position.x;
        int end_y = bullet_manager->bullets[i].position.y;

        if (!bullet_manager->bullets[i].is_player && SDL_IntersectRectAndLine(
            &player->rect, 
            &start_x, 
            &start_y, 
            &end_x,
            &end_y)) 
            {
            player->is_dead = true;  
            BulletManager_remove(bullet_manager, --i);
            
        }
    }
}


void level1_destroy(Mix_Music* bgMusic, BulletManager* bullet_manager, Entity* player, Tilemap *map, SDL_Texture* ammo_texture, SDL_Texture* ammo_fired_texture, AmmoBox *box) {
    SDL_DestroyTexture(ammo_texture);
    SDL_DestroyTexture(ammo_fired_texture);
    Mix_FreeMusic(bgMusic);
    Map_destroy(map);
    AmmoBox_destroy(box);
    BulletManager_destroy(bullet_manager);
    Entity_destroy(player);
}

void Hood_render(SDL_Renderer *renderer, Entity *player, SDL_Texture *ammo_texture, SDL_Texture *ammo_fired_texture){
    Vector2 initials = Vector2_new(40, 0);
    Vector2 gaps = Vector2_new(15, 35);
    Vector2 size = Vector2_new(12, 33);
    int row_capacity = 10;

    for (size_t i = 0; i < player->weapon->ammo_max; i++) {
        SDL_RenderCopy(
            renderer,
            (i < player->weapon->ammo ? ammo_texture : ammo_fired_texture),
            NULL,
            &(SDL_Rect) {
                initials.x + i % row_capacity * gaps.x,
                initials.y + i / row_capacity * gaps.y,
                size.x,
                size.y,
            }
        );
    }
}

void level1(GameState* PBState, CHARACTER_TYPE character_type) {
    // Variables initialization

    Tilemap *map = Map_parse(
        PBState->renderer,
        "./resource/maps/level1",
        "./resource/img/tiles/bg.png"
    );
    Entity *player = Player_new(
        PBState->renderer,
        character_type,
        (SDL_Rect) {
            1000,
            460,
            70,
            49,
        },
        Vector2_new(1, 0),
        7,
        250
    );
    AmmoBox *box = AmmoBox_new(PBState->renderer, 800, 160);
    BulletManager *bullet_manager = BulletManager_new(100);
    ExitCar *exit = ExitCar_new(PBState->renderer);
    PBState->bgMusic = Mix_LoadMUS("./resource/sound/MiamiDisco.mp3");
    Mix_PlayMusic(PBState->bgMusic, 0);
    SDL_Texture *ammo_texture;
    SDL_Texture *ammo_fired_texture;

    SDL_Texture *crosshair_texture = IMG_LoadTexture(PBState->renderer, "./resource/img/hud/ch.png");
    SDL_Rect crosshair_rect = Rect_new(630, 350, 20, 20);
    SDL_ShowCursor(false);

    Entity **enemies = malloc(sizeof(Entity *) * 3);
    enemies[0] = Enemy_new(PBState->renderer, SHOTGUNNER, Rect_new(100, 100, 60, 50), Vector2_new(0, 1), 3, 500);
    enemies[1] = Enemy_new(PBState->renderer, PISTOLER, Rect_new(250, 250, 60, 44), Vector2_new(1, 1), 3, 500);
    enemies[2] = Enemy_new(PBState->renderer, SHOTGUNNER, Rect_new(300, 500, 60, 50), Vector2_new(1, 0.7), 3, 500);

    EnemyManager *enemy_manager = EnemyManager_new(enemies, 3, 3);
    EnemyManager *player_manager = EnemyManager_new(&player, 1, 1);
    (void) player_manager;

    switch (character_type) {
        case SHAYLUSHAY:
            ammo_texture = IMG_LoadTexture(PBState->renderer, "./resource/img/hud/rifleAmmo.png");
            ammo_fired_texture = IMG_LoadTexture(PBState->renderer, "./resource/img/hud/rifleNoAmmo.png");
            break;
        case YALTPILS:
            ammo_texture = IMG_LoadTexture(PBState->renderer, "./resource/img/hud/pistolAmmo.png");
            ammo_fired_texture = IMG_LoadTexture(PBState->renderer, "./resource/img/hud/pistolNoAmmo.png");
            break;
        case DAWAWUE:
            ammo_texture = IMG_LoadTexture(PBState->renderer, "./resource/img/hud/shotgunAmmo.png");
            ammo_fired_texture = IMG_LoadTexture(PBState->renderer, "./resource/img/hud/shotgunNoAmmo.png");
            break;
    }
    
    Viewport viewport = Viewport_centralized(
        player->rect.x + player->pivot.x,
        player->rect.y + player->pivot.y,
        WINDOW_WIDTH,
        WINDOW_HEIGHT
    );

    // Main loop

    bool is_firing = false;

    while (PBState->run == LEVEL1) {
        int mouseX;
        int mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        crosshair_rect.x = mouseX - crosshair_rect.w / 2;
        crosshair_rect.y = mouseY - crosshair_rect.h / 2;

        Vector2 player_center = Vector2_new(
            player->rect.x + (player -> rect.w / 2.0),
            player->rect.y + (player -> rect.h / 2.0)
        );
        
        SDL_Point PlayerCenter = (SDL_Point) {
            player_center.x,
            player_center.y,
        };

        // Events
    
        while (SDL_PollEvent(&PBState->event)) {
            switch (PBState->event.type) {
                case SDL_QUIT:
                    PBState->run = QUIT;
                    break;
                case SDL_MOUSEBUTTONUP:
                    switch (PBState->event.button.button) {
                        case SDL_BUTTON_LEFT:
                            is_firing = false;
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch (PBState->event.button.button) {
                        case SDL_BUTTON_LEFT:
                            is_firing = true;
                            break;
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (PBState->event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            PBState->run = MENU;
                            break;
                        case SDLK_RETURN:
                            exit->is_opened = true;
                            break;
                        case SDLK_EQUALS:
                        case SDLK_KP_PLUS:
                            Mix_MasterVolume(Mix_MasterVolume(-1) + (MIX_MAX_VOLUME / 8));
                            Mix_VolumeMusic(Mix_VolumeMusic(-1) + (MIX_MAX_VOLUME / 8));
                            break;
                        case SDLK_MINUS:
                        case SDLK_KP_MINUS:
                            Mix_MasterVolume(Mix_MasterVolume(-1) - (MIX_MAX_VOLUME / 8));
                            Mix_VolumeMusic(Mix_VolumeMusic(-1) - (MIX_MAX_VOLUME / 8));
                            break;
                    }
                    break;
            }
        }

        if (is_firing) {
            Weapon_shoot(
                player->weapon,
                bullet_manager,
                Vector2_add(
                    player_center,
                    Vector2_with_magnitude(
                        player->direction,
                        player->rect.h / 2
                    )
                ),
                player->direction,
                true
            );
        }
        
        if(player->is_dead) {
            PBState->run = GAME_OVER;
            PBState->rerun = LEVEL1;
        }

        // Update

        BulletManager_update(bullet_manager, LEVEL_WIDTH, LEVEL_HEIGHT);
        Player_update(player, map, &viewport, Vector2_new(mouseX, mouseY));
        ExitCar_update(exit, PlayerCenter);
        EnemyManager_update(enemy_manager, player, map, bullet_manager);
        AmmoBox_update(box, player);
        bullet_collider_enemy(bullet_manager, enemy_manager, map);
        bullet_collider_player(bullet_manager, player, map);
        // Render
        
        SDL_SetRenderDrawColor(PBState->renderer, 0, 0, 0, 255);
        SDL_RenderClear(PBState->renderer);
        
        if (exit->is_opened && SDL_PointInRect(&PlayerCenter, &exit->seat_collider)) {
            PBState->run++;
        }
        if(enemy_manager->enemy_count == 0) {
            exit->is_opened = true;
        }
        
        AmmoBox_render(PBState->renderer, box, map);
        BulletManager_render(PBState->renderer, bullet_manager, map);
        Entity_render(PBState->renderer, player, map);
        ExitCar_render(PBState->renderer, exit, map);
        EnemyManager_render(enemy_manager, PBState->renderer, map);
        Map_render(map, PBState->renderer, &viewport);
        Hood_render(PBState->renderer, player, ammo_texture, ammo_fired_texture);
        SDL_RenderCopy(PBState->renderer, crosshair_texture, NULL, &crosshair_rect);

        SDL_RenderPresent(PBState->renderer);

        Map_initialize(map, PBState->renderer);

        SDL_Delay(1000 / 60);
    }

    SDL_ShowCursor(true);

    level1_destroy(PBState->bgMusic, bullet_manager, player, map, ammo_texture, ammo_fired_texture, box);
}

