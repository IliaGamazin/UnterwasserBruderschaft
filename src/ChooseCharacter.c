#include "Header_main.h"

#define BUTTON_COUNT_CHOOSE 3
#define CURRENT_LEVEL_CHOOSE level-1

void ChooseCharacter_destroy(Button *button_arr, SDL_Texture *bg_tex, Mix_Music *bg_mus, Mask **mask_arr) {
    for (int i = 0; i < BUTTON_COUNT_CHOOSE; i++) {
        Button_destroy(button_arr[i]);
        Mask_destroy(mask_arr[i]);
    }

    free(mask_arr);
    free(button_arr);
    SDL_DestroyTexture(bg_tex);
    Mix_FreeMusic(bg_mus);
}

void handle_pointing_choose(SDL_Point mouse_point, Button *button_arr, Mask **mask_arr, GameState *PBState) {
    for (int i = 0; i < BUTTON_COUNT_CHOOSE; i++) {
        if (SDL_PointInRect(&mouse_point, &button_arr[i].button_rect)) {

            SDL_SetCursor(PBState->handCursor);
            button_arr[i].hower = true;

            if (!button_arr[i].playing_sound) {
                Mix_PlayChannel(-1, button_arr[i].button_sound, 0);
                mask_arr[i]->is_animated = true;
                button_arr[i].playing_sound = true;
            }

            break;
        }
        else {
            SDL_SetCursor(PBState->arrowCursor);
            mask_arr[i]->is_animated = false;
            button_arr[i].hower = false;
            button_arr[i].playing_sound = false;
        }
    }    
}

CHARACTER_TYPE ChooseCharacter(GameState *PBState, SCENE level) {
    
    // Change game state variables

    PBState->bgTexture = IMG_LoadTexture(PBState->renderer, "media/img/chooseHero/chooseHeroBg.png");
    PBState->bgMusic = Mix_LoadMUS("media/sound/nightcall.mp3");
    Mix_PlayMusic(PBState->bgMusic, 0);

    // Initialize scene variables

    Mask **mask_arr = Mask_arr_new(PBState->renderer);

    Button *button_arr = Button_arr_new_choose(PBState->renderer);
	CHARACTER_TYPE char_type = 0;
    
    SDL_Texture *sha_border = IMG_LoadTexture(PBState->renderer, "media/img/chooseHero/chooseHeroSha.png");
    SDL_Texture *yal_border = IMG_LoadTexture(PBState->renderer, "media/img/chooseHero/chooseHeroYal.png");
    SDL_Texture *daw_border = IMG_LoadTexture(PBState->renderer, "media/img/chooseHero/chooseHeroDaw.png");

	while (PBState->run == CURRENT_LEVEL_CHOOSE) {
		while (SDL_PollEvent(&PBState->event)) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            SDL_Point mouse_point = { mouseX, mouseY };
            handle_pointing_choose(mouse_point, button_arr, mask_arr, PBState);

            if (PBState->event.type == SDL_QUIT) {
                PBState->run = QUIT;
            }

            if (PBState->event.type == SDL_MOUSEBUTTONDOWN) {
                if (SDL_PointInRect(&mouse_point, &button_arr[0].button_rect) || 
                    SDL_PointInRect(&mouse_point, &button_arr[1].button_rect)||
                    SDL_PointInRect(&mouse_point, &button_arr[2].button_rect)) {
                    
                    if(SDL_PointInRect(&mouse_point, &button_arr[SHAYLUSHAY].button_rect)){
                        char_type = SHAYLUSHAY;    
                    }

                    if(SDL_PointInRect(&mouse_point, &button_arr[YALTPILS].button_rect)){
                        char_type = YALTPILS;   
                    }

                    if(SDL_PointInRect(&mouse_point, &button_arr[DAWAWUE].button_rect)){
                        char_type = DAWAWUE;                        
                    }
                    
                    PBState->run++;
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

        SDL_RenderClear(PBState->renderer);
        SDL_RenderCopy(PBState->renderer, PBState->bgTexture, NULL, &PBState->bgRect);

        if (button_arr[SHAYLUSHAY].hower) {
            SDL_RenderCopy(PBState->renderer, sha_border, NULL, &PBState->bgRect);
        }
        else if (button_arr[YALTPILS].hower) {
            SDL_RenderCopy(PBState->renderer, yal_border, NULL, &PBState->bgRect);
        }
        else if (button_arr[DAWAWUE].hower) {
            SDL_RenderCopy(PBState->renderer, daw_border, NULL, &PBState->bgRect);
        }
        
        for (int i = 0; i < BUTTON_COUNT_CHOOSE; i++) {
            Button_render(PBState->renderer, button_arr[i]);
            Mask_render(PBState->renderer, mask_arr[i]);
        }

        SDL_RenderPresent(PBState->renderer);
        SDL_Delay(1000 / 60);
	}

    SDL_DestroyTexture(sha_border);
    SDL_DestroyTexture(yal_border);
    SDL_DestroyTexture(daw_border);
    SDL_SetCursor(PBState->arrowCursor);

    ChooseCharacter_destroy(button_arr, PBState->bgTexture, PBState->bgMusic, mask_arr);
    return char_type;
}
