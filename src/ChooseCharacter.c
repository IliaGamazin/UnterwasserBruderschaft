#include "Header_main.h"

void destroyChooseChar(Button* buttonArr, SDL_Texture* bgTexture, Mix_Music* bgMusic, Mask** maskArr) {
    for (int i = 0; i < BUTTON_COUNT_CHOOSE; i++)
    {
        destroyButton(buttonArr[i]);
        destroyMask(maskArr[i]);
    }
    free(maskArr);
    free(buttonArr);
    SDL_DestroyTexture(bgTexture);
    Mix_FreeMusic(bgMusic);
}
void handleButtonPointingChoose(SDL_Point mousePoint, Button* buttonArr, Mask** maskArr, GameState* PBState) {
    for (int i = 0; i < BUTTON_COUNT_CHOOSE; i++)
    {
        if (SDL_PointInRect(&mousePoint, &buttonArr[i].buttonRect) == true) {
            SDL_SetCursor(PBState->handCursor);
            buttonArr[i].isPointedAt = true;
            if (!buttonArr[i].isPlayingSound)
            {
                Mix_PlayChannel(-1, buttonArr[i].buttonSound, 0);
                maskArr[i]->isAnimated = true;
                buttonArr[i].isPlayingSound = true;
            }
            break;
        }
        else {
            SDL_SetCursor(PBState->arrowCursor);
            maskArr[i]->isAnimated = false;
            buttonArr[i].isPointedAt = false;
            buttonArr[i].isPlayingSound = false;
        }
    }
}

CHARACTER_TYPE chooseCharacter(GameState* PBState, SCENE level) {
	PBState->run = CURRENT_LEVEL_CHOOSE;
    PBState->bgTexture = IMG_LoadTexture(PBState->renderer, "media/img/lvl1_chooseHero.png");
    PBState->bgMusic = Mix_LoadMUS("media/sound/nightcall.mp3");

    Mix_PlayMusic(PBState->bgMusic, 0);
    Mask** maskArr = fillMaskArr(PBState->renderer);

    Button* buttonArr = fillButtonArrChoose(PBState->renderer);
	CHARACTER_TYPE charType = 0;
	while (PBState->run == CURRENT_LEVEL_CHOOSE) {
		while (SDL_PollEvent(&PBState->event)) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            SDL_Point mousePoint = { mouseX, mouseY };
            handleButtonPointingChoose(mousePoint, buttonArr, maskArr, PBState);
            if (PBState->event.type == SDL_QUIT) {
                PBState->run = -1;
            }
            if (PBState->event.type == SDL_MOUSEBUTTONDOWN) {
                    if (SDL_PointInRect(&mousePoint, &buttonArr[0].buttonRect) || SDL_PointInRect(&mousePoint, &buttonArr[1].buttonRect)||SDL_PointInRect(&mousePoint, &buttonArr[2].buttonRect)) {
                        if(SDL_PointInRect(&mousePoint, &buttonArr[0].buttonRect)){
                            charType = SHAYLUSHAY;
                        }
                        if(SDL_PointInRect(&mousePoint, &buttonArr[1].buttonRect)){
                            charType = YALTPILS;
                        }
                        if(SDL_PointInRect(&mousePoint, &buttonArr[2].buttonRect)){
                            charType = DAWAWUE;
                        }
                        PBState->run++;
                    }                      
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
                case SDLK_ESCAPE:
                    PBState->run = MENU;
                    break;
                }
                Mix_Volume(-1, PBState->volume);
                Mix_VolumeMusic(PBState->volume);
            }
		}
        SDL_RenderCopy(PBState->renderer, PBState->bgTexture, NULL, &PBState->bgRect);
        
        for (int i = 0; i < BUTTON_COUNT_CHOOSE; i++)
        {
            showButton(PBState->renderer, buttonArr[i]);
            animMask(PBState->renderer, maskArr[i]);
        }
        SDL_RenderPresent(PBState->renderer);
        SDL_Delay(1000 / 60);
	}
    SDL_SetCursor(PBState->arrowCursor);
    destroyChooseChar(buttonArr, PBState->bgTexture, PBState->bgMusic, maskArr);
    return charType;
}