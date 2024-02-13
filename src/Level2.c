#include "../include/Header_main.h"

void level2(GameState *PBState, CHARACTER_TYPE char_type) {
    Player *player_drive = player_drive_new(PBState->renderer, 200, 200, char_type);
    BackgroundManager *bg_manager = bg_manager_new(PBState->renderer, 10);
    ObstaclesManager *ob_manager = obstacle_manager_new(10, 3, 100);
    bool key_up = false;
    bool key_down = false;
    while (PBState->run == LEVEL2) {
        while (SDL_PollEvent(&PBState->event)) {
       
            if (PBState->event.type == SDL_QUIT) {
                PBState->run = QUIT;
            }
            
            if (PBState->event.type == SDL_KEYDOWN) {
                switch (PBState->event.key.keysym.sym) {
                case SDLK_w:
                    key_up = true;
                    break;
                case SDLK_s:
                    key_down = true;
                    break;
                case SDLK_ESCAPE:
                    PBState->run = MENU;
                    break;
                }
            }
            else if (PBState->event.type == SDL_KEYUP) {
                switch (PBState->event.key.keysym.sym) {
                case SDLK_w:
                    key_up = false;
                    break;
                case SDLK_s:
                    key_down = false;
                    break;
                }
            } 
        }
        spawn_obstacles(ob_manager, PBState->renderer);
        obstacle_manager_update(ob_manager, 5); //Change for player vel_x

        SDL_RenderClear(PBState->renderer);
        bg_manager_update(bg_manager);
        player_drive_update(player_drive, key_up, key_down);
        bg_manager_render(bg_manager, PBState->renderer);
        obstacle_manager_render(ob_manager, PBState->renderer);
        player_drive_render(player_drive, PBState->renderer);
        
        // Collision

        // Render
        SDL_RenderPresent(PBState->renderer);

        SDL_Delay(1000 / 60);

    }
    obstacle_manager_destroy(ob_manager);
    bg_manager_destroy(bg_manager);
    player_drive_destroy(player_drive);
}

