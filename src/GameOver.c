#include "../inc/Header_main.h"

// Game Over

void gamover_destroy(SoundBar *bar, SDL_Texture *bgTexture, Mix_Music *bgMusic, Mask *m, Button *button_arr) {
    Mask_destroy(m);
    Button_destroy(button_arr[0]);
    Button_destroy(button_arr[1]);
    free(button_arr);
    SoundBar_destroy(bar);
    Mix_FreeMusic(bgMusic);
    SDL_DestroyTexture(bgTexture);
}

void gameover(GameState *PBState) {

    //Scene variables initialization

    PBState->bgRect = Rect_new(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    PBState->bgTexture = IMG_LoadTexture(PBState->renderer, "./resource/img/gameover/gameover_bg.png");
    PBState->bgMusic = Mix_LoadMUS("./resource/sound/zrada.mp3");

    Mask *mask_zrada = Mask_gameover_new(PBState->renderer);
    SoundBar *bar = SoundBar_new(PBState->renderer, 0, 0, Mix_MasterVolume(-1) * 3, 30);
    Button *button_arr = malloc(sizeof(Button) * 2);

    button_arr[0] = Button_new(390, 500, 500, 60, IMG_LoadTexture(PBState->renderer, "./resource/img/gameover/try_idle.png"), IMG_LoadTexture(PBState->renderer, "./resource/img/gameover/try_active.png"), Mix_LoadWAV("./resource/sound/pointSound.wav"));
    button_arr[1] = Button_new(390, 600, 500, 60, IMG_LoadTexture(PBState->renderer, "./resource/img/gameover/exit_idle.png"), IMG_LoadTexture(PBState->renderer, "./resource/img/gameover/exit_active.png"), Mix_LoadWAV("./resource/sound/pointSound.wav"));

    // Change game state variables 

    SDL_QueryTexture(PBState->bgTexture, NULL, NULL, &PBState->bgRect.w, &PBState->bgRect.h);
    Mix_PlayMusic(PBState->bgMusic, 0);

    mask_zrada->is_animated = true;

    // Scene loop

    while (PBState->run == GAME_OVER) {
        while (SDL_PollEvent(&PBState->event)) {
            if (PBState->event.type == SDL_QUIT) {
                PBState->run = QUIT;
            }

            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            SDL_Point mouse_point = { mouseX, mouseY };

            for(int i = 0; i < 2; i++) {
                if (SDL_PointInRect(&mouse_point, &button_arr[i].button_rect)) {
                    SDL_SetCursor(PBState->handCursor);
                    button_arr[i].hower = true;

                    if (!button_arr[i].playing_sound) {
                        Mix_PlayChannel(-1, button_arr[i].button_sound, 0);
                        button_arr[i].playing_sound = true;
                    }

                    button_arr[i].button_rect.x = WINDOW_WIDTH / 2 - 250;
                    button_arr[i].button_rect.w = 516;
                    button_arr[i].button_rect.h = 68;

                    break;
                }

                else {
                    SDL_SetCursor(PBState->arrowCursor);

                    button_arr[i].hower = false;
                    button_arr[i].playing_sound = false;

                    button_arr[i].button_rect.x = WINDOW_WIDTH / 2 - 242;
                    button_arr[i].button_rect.w = 500;
                    button_arr[i].button_rect.h = 60;
                }
            }

            if (PBState->event.type == SDL_MOUSEBUTTONDOWN) {
                if (button_arr[0].hower) {
                    PBState->run = PBState->rerun;
                }
                else if (button_arr[1].hower) {
                    PBState->run = MENU;
                }
            }

            else if (PBState->event.type == SDL_KEYDOWN) {
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
            }
        }
        
        SoundBar_update(bar, Mix_MasterVolume(-1));

        SDL_RenderClear(PBState->renderer);
        SDL_RenderCopy(PBState->renderer, PBState->bgTexture, NULL, &PBState->bgRect);
        SDL_RenderCopy(PBState->renderer, bar->texture, NULL, &bar->rect);
        Mask_render(PBState->renderer, mask_zrada);
        Button_render(PBState->renderer, button_arr[0]);
        Button_render(PBState->renderer, button_arr[1]);
        SDL_RenderPresent(PBState->renderer);
        
        SDL_Delay(1000 / 60);
    }

    SDL_RenderClear(PBState->renderer);
    gamover_destroy(bar,PBState->bgTexture, PBState->bgMusic, mask_zrada, button_arr);
}

