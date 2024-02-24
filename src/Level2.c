#include "../inc/Header_main.h"

void level2_destroy(ObstaclesManager *ob_manager, BackgroundManager *bg_manager, Player *player_drive, Mix_Music *bg_music, t_Timer *timer) {
    timer_destroy(timer);
    obstacle_manager_destroy(ob_manager);
    bg_manager_destroy(bg_manager);
    player_drive_destroy(player_drive);
    Mix_FreeMusic(bg_music);
}

void level2(GameState *PBState, CHARACTER_TYPE char_type) {
    PBState->bgMusic = Mix_LoadMUS("./resource/sound/nightcall.mp3");

    Player *player_drive = player_drive_new(PBState->renderer, 200, 200, char_type);
    BackgroundManager *bg_manager = bg_manager_new(PBState->renderer, player_drive->velocity_x);
    ObstaclesManager *ob_manager = obstacle_manager_new(10, 3, 100);
    t_Timer *timer = timer_new(60, PBState->renderer); 

    Mix_PlayMusic(PBState->bgMusic, 0);

    int finish_distance = 30000;

    bool key_up = false;
    bool key_gas = false;
    bool key_break = false;
    bool key_down = false;

    while (PBState->run == LEVEL2) {
        while (SDL_PollEvent(&PBState->event)) {

            if (PBState->event.type == SDL_QUIT) {
                PBState->run = QUIT;
            }
            
            if (PBState->event.type == SDL_KEYDOWN) {
                switch (PBState->event.key.keysym.sym) {
                case SDLK_a:
                    key_break = true;
                    break;
                case SDLK_d:
                    key_gas = true;
                    break;
                case SDLK_w:
                    key_up = true;
                    break;
                case SDLK_s:
                    key_down = true;
                    break;
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
            }
            else if (PBState->event.type == SDL_KEYUP) {
                switch (PBState->event.key.keysym.sym) {
                case SDLK_a:
                    key_break = false;
                    break;
                case SDLK_d:
                    key_gas = false;
                    break;
                case SDLK_w:
                    key_up = false;
                    break;
                case SDLK_s:
                    key_down = false;
                    break;
                } 
                Mix_LoadMUS("./resource/sound/nightcall.mp3");
            } 
        }

        if (player_drive->velocity_x >= player_drive->initial_velocity_x / 2 && key_break) {
            --player_drive->velocity_x;
        }

        if (player_drive->velocity_x < player_drive->initial_velocity_x && key_gas) {
            ++player_drive->velocity_x;
        }

        if (player_drive->passed_distance >= finish_distance) {
            PBState->run = MENU;
        }

        SDL_RenderClear(PBState->renderer);

        // Level update

        timer_update(timer);
        spawn_obstacles(ob_manager, PBState->renderer);
        obstacle_manager_update(ob_manager, player_drive->velocity_x); 
        bg_manager_update(bg_manager, player_drive->velocity_x);
        player_drive_update(player_drive, key_up, key_down);

        // Level render

        bg_manager_render(bg_manager, PBState->renderer);
        obstacle_manager_render(ob_manager, PBState->renderer);
        player_drive_render(player_drive, PBState->renderer);
        timer_render(timer, PBState->renderer);

        // Collision

        if (player_check_collision(ob_manager, player_drive)) {
            PBState->run = MENU;
        }
        
        // Render

        SDL_RenderPresent(PBState->renderer);
        SDL_Delay(1000 / 60);

    }

    level2_destroy(ob_manager, bg_manager, player_drive, PBState->bgMusic, timer);
}

