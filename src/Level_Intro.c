#include "../inc/Header_main.h"

// Intro 

void intro_destroy(SoundBar *Bar, SDL_Texture *bgTexture, Mix_Music *bgMusic, Mask *m) {
    Mask_destroy(m);
    SoundBar_destroy(Bar);
    Mix_FreeMusic(bgMusic);
    SDL_DestroyTexture(bgTexture);
}

void level_intro(GameState *PBState, SCENE intro_type) {
    //Scene variables initialization

    PBState->bgRect = Rect_new(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    Mask *mask_sprite = NULL;
    SoundBar *Bar = SoundBar_new(PBState->renderer, 0, 0, Mix_MasterVolume(-1) * 3, 30);

    // Change game state variables 

    switch (intro_type) {
        case INTRO_1:
            PBState->bgTexture = IMG_LoadTexture(PBState->renderer, "./resource/img/intros/main_intro1.png");
            PBState->bgMusic = Mix_LoadMUS("./resource/sound/intro_theme.mp3");
            mask_sprite = Mask_new(PBState->renderer, YALTPILS, 1000, 540, 170, 170);
            break;
        case INTRO_2:
            PBState->bgTexture = IMG_LoadTexture(PBState->renderer, "./resource/img/intros/main_intro2.png");
            PBState->bgMusic = Mix_LoadMUS("./resource/sound/intro_theme.mp3");
            mask_sprite = Mask_new(PBState->renderer, SHAYLUSHAY, 1000, 540, 170, 170);
            break;
        case LEVEL1_INTRO:
            PBState->bgTexture = IMG_LoadTexture(PBState->renderer, "./resource/img/lvl1_intro_bg.png");
            PBState->bgMusic = Mix_LoadMUS("./resource/sound/nightcall.mp3");
            mask_sprite = Mask_new(PBState->renderer, DAWAWUE, 10, 10, 170, 170);
            break;
        case LEVEL2_INTRO:
            PBState->bgTexture = IMG_LoadTexture(PBState->renderer, "./resource/img/lvl2_intro_bg.png");
            PBState->bgMusic = Mix_LoadMUS("./resource/sound/nightcall.mp3");
            mask_sprite = Mask_new(PBState->renderer, SHAYLUSHAY, 10, 10, 170, 170);
            break;
        case LEVEL3_INTRO:
            PBState->bgTexture = IMG_LoadTexture(PBState->renderer, "./resource/img/lvl3_intro_bg.png");
            PBState->bgMusic = Mix_LoadMUS("./resource/sound/nightcall.mp3");
            mask_sprite = Mask_new(PBState->renderer, YALTPILS, 10, 10, 170, 170);
            break;
        default:
            break;
    }

    SDL_QueryTexture(PBState->bgTexture, NULL, NULL, &PBState->bgRect.w, &PBState->bgRect.h);
    SDL_DestroyTexture(mask_sprite->mask_tex_active);

    Mix_PlayMusic(PBState->bgMusic, 0);

    mask_sprite->mask_tex_active = mask_sprite->mask_tex_idle;
    mask_sprite->is_animated = true;

    // Scene loop

    while (PBState->run == intro_type) {
        while (SDL_PollEvent(&PBState->event)) {
            if (PBState->event.type == SDL_QUIT) {
                PBState->run = QUIT;
            }
            else if (PBState->event.type == SDL_KEYDOWN) {
                switch (PBState->event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        PBState->run = MENU;
                        break;
                    case SDLK_RETURN:
                        PBState->run++;
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

        SoundBar_update(Bar, Mix_MasterVolume(-1));
        SDL_RenderClear(PBState->renderer);
        SDL_RenderCopy(PBState->renderer, PBState->bgTexture, NULL, &PBState->bgRect);
        SDL_RenderCopy(PBState->renderer, Bar->texture, NULL, &Bar->rect);
        Mask_render(PBState->renderer, mask_sprite);
        SDL_RenderPresent(PBState->renderer);
        
        SDL_Delay(1000 / 60);
    }

    SDL_RenderClear(PBState->renderer);
    intro_destroy(Bar,PBState->bgTexture, PBState->bgMusic, mask_sprite);
}

