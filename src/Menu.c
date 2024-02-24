#include "../inc/Header_main.h"

// Menu scene function

void menu(GameState* PBState){
    // Change game state variables 

    PBState->run = MENU;
    PBState->bgTexture = IMG_LoadTexture(PBState->renderer, "media/img/menu/menu_bg.png");
    PBState->bgRect = Rect_new(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    PBState->bgMusic = Mix_LoadMUS("media/sound/nightcall.mp3");

    SDL_QueryTexture(PBState->bgTexture, NULL, NULL, &PBState->bgRect.w, &PBState->bgRect.h);
    Mix_PlayMusic(PBState->bgMusic, 0);

    // Initialize scene variables

    bool is_quitting = false;
    int quit_speed = 1;

    Button *button_arr = Button_arr_new_menu((WINDOW_WIDTH - BUTTON_WIDTH) - 17, BUTTON_GAP * 1.5, BUTTON_WIDTH, BUTTON_HEIGHT, PBState->renderer);
    SoundBar *Bar = SoundBar_new(PBState->renderer, 185, 690, Mix_MasterVolume(-1) * 3, 30);
    Mix_Chunk *exit_sound = Mix_LoadWAV("media/sound/carPass.wav");

    // Scene loop

    while (PBState->run == MENU) {
        while (SDL_PollEvent(&PBState->event)) {
            if (PBState->event.type == SDL_QUIT) {
                PBState->run = QUIT;
            }

            // Handle mouse input

            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            SDL_Point mouse_point = { mouseX, mouseY };

            if (!is_quitting) {
                handle_pointing_menu(mouse_point, button_arr, PBState);
            }

            if (PBState->event.type == SDL_MOUSEBUTTONDOWN) {
                for (int i = 0; i < BUTTON_COUNT_MENU; i++) {
                    if (SDL_PointInRect(&mouse_point, &button_arr[i].button_rect)) {
                        switch (i) {
                            case START_BUTTON:
                                PBState->run = INTRO_1;
                                break;
                            case FIRST_LEVEL_BUTTON:
                                PBState->run = LEVEL1_INTRO;
                                break;
                            case SECOND_LEVEL_BUTTON:
                                PBState->run = LEVEL2_INTRO;
                                break;
                            case THIRD_LEVEL_BUTTON:
                                PBState->run = LEVEL3;
                                break;
                            case EXIT_BUTTON:
                                if (!is_quitting) {
                                    is_quitting = true;
                                    Mix_PlayChannel(-1, exit_sound, 0);
                                }
                                break;
                        }
                    }
                }
            }

            // Handle keyboard input
            
            else if (PBState->event.type == SDL_KEYDOWN) {
                switch (PBState->event.key.keysym.sym) {
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
        }

        // Quit animation

        if (is_quitting) {
            button_arr[BUTTON_COUNT_MENU - 1].button_rect.x -= quit_speed;
            quit_speed += 1;

            if (button_arr[BUTTON_COUNT_MENU - 1].button_rect.x < -BUTTON_WIDTH) {
                PBState->run = QUIT;
            }
        }
        
        // Render the scene

        SoundBar_update(Bar, Mix_MasterVolume(-1));
        SDL_RenderCopy(PBState->renderer, PBState->bgTexture, NULL, &PBState->bgRect);
        SDL_RenderCopy(PBState->renderer, Bar->texture, NULL, &Bar->rect);
        
        for (int i = 0; i < BUTTON_COUNT_MENU; i++) {
            Button_render(PBState->renderer, button_arr[i]);
        }

        SDL_RenderPresent(PBState->renderer);
        SDL_Delay(1000 / 60);
    }

    // Destroy the scene

    SDL_RenderClear(PBState->renderer);
    SDL_SetCursor(PBState->arrowCursor);
    destroyMenu(button_arr, PBState->bgTexture, Bar, PBState->bgMusic, exit_sound);
}

