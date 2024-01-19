#include "Header_main.h"

void ChooseCharacter_destroy(Button* buttonArr, SDL_Texture* bgTexture, Mix_Music* bgMusic, Mask** maskArr) {
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

CHARACTER_TYPE ChooseCharacter(GameState* PBState, SCENE level) {
    PBState->bgTexture = IMG_LoadTexture(PBState->renderer, "media/img/chooseHero/chooseHeroBg.png");
    PBState->bgMusic = Mix_LoadMUS("media/sound/nightcall.mp3");

    Mix_PlayMusic(PBState->bgMusic, 0);
    Mask** maskArr = fillMaskArr(PBState->renderer);

    Button* buttonArr = fillButtonArrChoose(PBState->renderer);
	CHARACTER_TYPE charType = 0;
    
    SDL_Texture* shaBorder = IMG_LoadTexture(PBState->renderer, "media/img/chooseHero/chooseHeroSha.png");
    SDL_Texture* yalBorder = IMG_LoadTexture(PBState->renderer, "media/img/chooseHero/chooseHeroYal.png");
    SDL_Texture* dawBorder = IMG_LoadTexture(PBState->renderer, "media/img/chooseHero/chooseHeroDaw.png");
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
                    if(SDL_PointInRect(&mousePoint, &buttonArr[SHAYLUSHAY].buttonRect)){
                        charType = SHAYLUSHAY;    
                    }
                    if(SDL_PointInRect(&mousePoint, &buttonArr[YALTPILS].buttonRect)){
                        charType = YALTPILS;   
                    }
                    if(SDL_PointInRect(&mousePoint, &buttonArr[DAWAWUE].buttonRect)){
                        charType = DAWAWUE;                        
                    }
                    PBState->run++;
                }                    
            }
            else if (PBState->event.type == SDL_KEYDOWN) {
                switch (PBState->event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        PBState -> run = MENU;
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
        if (buttonArr[SHAYLUSHAY].isPointedAt)
        {
            SDL_RenderCopy(PBState->renderer, shaBorder, NULL, &PBState->bgRect);
        }
        else if (buttonArr[YALTPILS].isPointedAt)
        {
            SDL_RenderCopy(PBState->renderer, yalBorder, NULL, &PBState->bgRect);
        }
        else if (buttonArr[DAWAWUE].isPointedAt)
        {
            SDL_RenderCopy(PBState->renderer, dawBorder, NULL, &PBState->bgRect);
        }
        
        for (int i = 0; i < BUTTON_COUNT_CHOOSE; i++)
        {
            showButton(PBState->renderer, buttonArr[i]);
            animMask(PBState->renderer, maskArr[i]);
        }
        SDL_RenderPresent(PBState->renderer);
        SDL_Delay(1000 / 60);
	}
    SDL_DestroyTexture(shaBorder);
    SDL_DestroyTexture(yalBorder);
    SDL_DestroyTexture(dawBorder);
    SDL_SetCursor(PBState->arrowCursor);
    ChooseCharacter_destroy(buttonArr, PBState->bgTexture, PBState->bgMusic, maskArr);
    return charType;
}
