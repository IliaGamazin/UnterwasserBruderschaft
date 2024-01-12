#include "Header_main.h"

void destroyIntro(SoundBar* Bar, SDL_Texture* bgTexture, Mix_Music* bgMusic, Mask* m) {
    destroyMask(m);
    destroyBar(Bar);
    Mix_FreeMusic(bgMusic);
    SDL_DestroyTexture(bgTexture);
}

void levelIntro(GameState* PBState, SCENE level) {
    PBState->bgRect = createRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    PBState->run = CURRENT_LEVEL_INTRO;
    switch (level)
    {
    case LEVEL1:
        PBState->run = LEVEL1_INTRO;
        PBState->bgTexture = IMG_LoadTexture(PBState->renderer, "media/img/lvl1_intro_bg.png");
        PBState->bgMusic = Mix_LoadMUS("media/sound/nightcall.mp3");
        break;
    case LEVEL2:
        PBState->run = LEVEL2_INTRO;
        PBState->bgTexture = IMG_LoadTexture(PBState->renderer, "media/img/lvl2_intro_bg.png");
        PBState->bgMusic = Mix_LoadMUS("media/sound/nightcall.mp3");
        break;
    case LEVEL3:
        PBState->run = LEVEL3_INTRO;
        PBState->bgTexture = IMG_LoadTexture(PBState->renderer, "media/img/lvl3_intro_bg.png");
        PBState->bgMusic = Mix_LoadMUS("media/sound/nightcall.mp3");
        break;
    case LEVEL_SECRET:
        PBState->run = LEVEL_SECRET_INTRO;
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
    SoundBar* Bar = createSoundBar(600, 20, PBState->volume * 3, 30, PBState->renderer);
    while (PBState->run == CURRENT_LEVEL_INTRO) {
        while (SDL_PollEvent(&PBState->event)) {
            if (PBState->event.type == SDL_QUIT) {
                PBState->run = -1;
            }
            else if (PBState->event.type == SDL_KEYDOWN) {
                switch (PBState->event.key.keysym.sym) {
                case SDLK_EQUALS:
                    printf("\n Volume: %d", PBState->volume);
                    if (PBState->volume < MAX_VOLUME) {
                        PBState->volume += MAX_VOLUME / 10;
                    }
                    else {
                        PBState->volume = MAX_VOLUME;
                    }
                    break;
                case SDLK_MINUS:
                    printf("\n Volume: %d", PBState->volume);
                    if (PBState->volume > 0) {
                        PBState->volume -= MAX_VOLUME / 10;
                    }
                    else {
                        PBState->volume = 0;
                    }
                    break;
                case SDLK_RETURN:
                    PBState->run++;
                    break;              
                case SDLK_ESCAPE:
                    PBState->run = MENU;
                    break;
                }
                Mix_Volume(-1, PBState->volume);
                Mix_VolumeMusic(PBState->volume);
            }
        }
        updateSoundBar(Bar, PBState->volume);
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
