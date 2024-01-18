#include "Header_main.h"

void destroyIntro(SoundBar* Bar, SDL_Texture* bgTexture, Mix_Music* bgMusic, Mask* m) {
    destroyMask(m);
    destroyBar(Bar);
    Mix_FreeMusic(bgMusic);
    SDL_DestroyTexture(bgTexture);
}

void levelIntro(GameState* PBState, SCENE introNum) {
    PBState->bgRect = createRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    switch (introNum)
    {
    case LEVEL1_INTRO:
        PBState->bgTexture = IMG_LoadTexture(PBState->renderer, "media/img/lvl1_intro_bg.png");
        PBState->bgMusic = Mix_LoadMUS("media/sound/nightcall.mp3");
        break;
    case LEVEL2:
        PBState->bgTexture = IMG_LoadTexture(PBState->renderer, "media/img/lvl2_intro_bg.png");
        PBState->bgMusic = Mix_LoadMUS("media/sound/nightcall.mp3");
        break;
    case LEVEL3:
        PBState->bgTexture = IMG_LoadTexture(PBState->renderer, "media/img/lvl3_intro_bg.png");
        PBState->bgMusic = Mix_LoadMUS("media/sound/nightcall.mp3");
        break;
    case LEVEL_SECRET:
        PBState->bgTexture = IMG_LoadTexture(PBState->renderer, "media/img/lvl1_intro_bg.png");
        PBState->bgMusic = Mix_LoadMUS("media/sound/nightcall.mp3");
        break;
    default:
        break;
    }
    SDL_QueryTexture(PBState->bgTexture, NULL, NULL, &PBState->bgRect.w, &PBState->bgRect.h);

    Mask* textMask = createMask(PBState->renderer, SHAYLUSHAY, 10, 10, 170, 170);
    textMask->isAnimated = true;
    SDL_DestroyTexture(textMask->maskTextureActive);
    textMask->maskTextureActive = textMask->maskTextureIdle;
    Mix_PlayMusic(PBState->bgMusic, 0);
    SoundBar* Bar = createSoundBar(600, 20, Mix_MasterVolume(-1) * 3, 30, PBState->renderer);

    while (PBState->run == introNum) {
        while (SDL_PollEvent(&PBState->event)) {
            if (PBState->event.type == SDL_QUIT) {
                PBState->run = -1;
            }
            else if (PBState->event.type == SDL_KEYDOWN) {
                switch (PBState->event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        PBState -> run = MENU;
                        break;
                    case SDLK_RETURN:
                        PBState -> run++;
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
        updateSoundBar(Bar, Mix_MasterVolume(-1));
        SDL_RenderClear(PBState->renderer);
        SDL_RenderCopy(PBState->renderer, PBState->bgTexture, NULL, &PBState->bgRect);
        SDL_RenderCopy(PBState->renderer, Bar->barTexture, NULL, &Bar->barRect);
        animMask(PBState->renderer, textMask);
        SDL_RenderPresent(PBState->renderer);
        
        SDL_Delay(1000 / 60);
    }
    SDL_RenderClear(PBState->renderer);
    destroyIntro(Bar,PBState->bgTexture, PBState->bgMusic, textMask);
}
