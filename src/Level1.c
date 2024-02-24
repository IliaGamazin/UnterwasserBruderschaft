#include "../inc/Header_main.h"
#include "../inc/Camera.h"

void level1_destroy(Mix_Music* bgMusic, BulletManager* bullet_manager, Entity* player, Tilemap map, SDL_Texture* ammo_texture, SDL_Texture* ammo_fired_texture, AmmoBox box) {
    SDL_DestroyTexture(ammo_texture);
    SDL_DestroyTexture(ammo_fired_texture);
    Mix_FreeMusic(bgMusic);
    Map_destroy(map);
    AmmoBox_destroy(box);
    BulletManager_destroy(bullet_manager);
    Entity_destroy(player);
}

void updateCameraPosition(Camera* camera, Entity* player, int levelWidth, int levelHeight) {
    camera->position.x = (player->rect.x + player->rect.w / 2) - WINDOW_WIDTH / 2;
    camera->position.y = (player->rect.y + player->rect.h / 2) - WINDOW_HEIGHT / 2;

    // Clamp the camera
    
    if (camera->position.x < 0) { camera->position.x = 0; }
    if (camera->position.y < 0) { camera->position.y = 0; }
    if (camera->position.x > levelWidth - camera->viewPort.w) {
        camera->position.x = levelWidth - camera->viewPort.w;
    }
    if (camera->position.y > levelHeight - camera->viewPort.h) {
        camera->position.y = levelHeight - camera->viewPort.h;
    }
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

    Tilemap map = Map_new(PBState->renderer);
    Entity *player = Player_new(
        PBState->renderer,
        character_type,
        (SDL_Rect) {
            640,
            460,
            70,
            49,
        },
        Vector2_new(1, 0),
        7,
        500
    );
    AmmoBox box = AmmoBox_new(PBState->renderer, 800, 160);
    BulletManager *bullet_manager = BulletManager_new(100);
    ExitCar *exit = ExitCar_new(PBState->renderer);
    PBState->bgMusic = Mix_LoadMUS("./resource/sound/MiamiDisco.mp3");
    Mix_PlayMusic(PBState->bgMusic, 0);
    SDL_Texture *ammo_texture;
    SDL_Texture *ammo_fired_texture;

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
    
    Camera camera = {{0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, {0, 0}};

    // Main loop
    
    while (PBState->run == LEVEL1) {
        updateCameraPosition(&camera, player, LEVEL_WIDTH, LEVEL_HEIGHT);
        int mouseX;
        int mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        mouseX += camera.position.x;
        mouseY += camera.position.y;
        
        Vector2 player_center = Vector2_new(
            player->rect.x + (player -> rect.w / 2.0),
            player->rect.y + (player -> rect.h / 2.0)
        );
        
        player->direction = Vector2_from_points(
                player_center,
                Vector2_new(mouseX, mouseY)
            );
        
        SDL_Point PlayerCenter = (SDL_Point) {
            player_center.x,
            player_center.y,
        };

        player -> direction = Vector2_from_points(
            player_center,
            Vector2_new(mouseX, mouseY)
        );

        updateCameraPosition(&camera, player, LEVEL_WIDTH, LEVEL_HEIGHT);

        // Events

        while (SDL_PollEvent(&PBState->event)) {
            switch (PBState->event.type) {
                case SDL_QUIT:
                    PBState->run = QUIT;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch (PBState->event.button.button) {
                        case SDL_BUTTON_LEFT:
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
                                player->direction
                            );
                            break;
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (PBState->event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            PBState->run = MENU;
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

        // Update

        BulletManager_update(bullet_manager, LEVEL_WIDTH, LEVEL_HEIGHT);

        Player_update(player);
        ExitCar_update(exit, PlayerCenter);

        // Render
        
        SDL_SetRenderDrawColor(PBState->renderer, 0, 0, 0, 255);
        SDL_RenderClear(PBState -> renderer);
        
        if (exit->is_opened && SDL_PointInRect(&PlayerCenter, &exit->seat_collider)) {
            PBState->run = MENU;
        }
        
        Map_render(map, PBState->renderer, camera);
        AmmoBox_render(PBState->renderer, box, camera);
        BulletManager_render(PBState->renderer, bullet_manager, camera);
        Entity_render(PBState->renderer, player, camera);
        ExitCar_render(PBState->renderer, exit, camera);
        Hood_render(PBState -> renderer, player, ammo_texture, ammo_fired_texture);


        SDL_RenderPresent(PBState->renderer);
        SDL_Delay(1000 / 60);
    }

    level1_destroy(PBState->bgMusic, bullet_manager, player, map, ammo_texture, ammo_fired_texture, box);
}

