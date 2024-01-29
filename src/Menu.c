#include "Header_main.h"

void menu(GameState* PBState){
    Mix_Chunk* exitSound = Mix_LoadWAV("media/sound/carPass.wav");
    bool quitTimeFlag = false;
    int quitButtonSpeed = 1;
    PBState->run = MENU;
    
    PBState->bgTexture = IMG_LoadTexture(PBState->renderer, "media/img/menu/menu_bg.png");
    PBState->bgRect = createRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_QueryTexture(PBState->bgTexture, NULL, NULL, &PBState->bgRect.w, &PBState->bgRect.h);

    PBState->bgMusic = Mix_LoadMUS("media/sound/nightcall.mp3");
    Mix_PlayMusic(PBState->bgMusic, 0);

    Button* buttonArr = fillButtonArrMenu((WINDOW_WIDTH - BUTTON_WIDTH) - 17, BUTTON_GAP * 1.5, BUTTON_WIDTH, BUTTON_HEIGHT, PBState->renderer);
    SoundBar* Bar = createSoundBar(185, 690, Mix_MasterVolume(-1) * 3, 30, PBState->renderer);
    while (PBState->run == MENU) {
        while (SDL_PollEvent(&PBState->event)) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            SDL_Point mousePoint = { mouseX, mouseY };
            if (!quitTimeFlag)
            {
                handleButtonPointingMenu(mousePoint, buttonArr, PBState);
            }
            if (PBState->event.type == SDL_QUIT) {
                PBState->run = QUIT;
            }
            if (PBState->event.type == SDL_MOUSEBUTTONDOWN) {
                for (int i = 0; i < BUTTON_COUNT_MENU; i++)
                {
                    if (SDL_PointInRect(&mousePoint, &buttonArr[i].buttonRect) == true) {
                        switch (i)
                        {
                        case START_BUTTON:
                            PBState->run = INTRO_1;
                            printf("\nStart button");
                            break;
                        case FIRST_LEVEL_BUTTON:
                            printf("\nFirst level");
                            PBState->run = LEVEL1_INTRO;
                            break;
                        case SECOND_LEVEL_BUTTON:
                            printf("\nSecond level");
                            PBState->run = LEVEL2;
                            break;
                        case THIRD_LEVEL_BUTTON:
                            printf("\nThird level");
                            PBState->run = LEVEL3;
                            break;
                        case EXIT_BUTTON:
                            if (!quitTimeFlag)
                            {
                                printf("\nExit button");
                                
                                quitTimeFlag = true;
                                Mix_PlayChannel(-1, exitSound, 0);
                            }
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
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
        if (quitTimeFlag == true)
        {
            buttonArr[BUTTON_COUNT_MENU - 1].buttonRect.x -= quitButtonSpeed;
            quitButtonSpeed += 1;
            if (buttonArr[BUTTON_COUNT_MENU - 1].buttonRect.x < -BUTTON_WIDTH)
            {
                PBState->run = QUIT;
            }
        }
        updateSoundBar(Bar, Mix_MasterVolume(-1));
        SDL_RenderCopy(PBState->renderer, PBState->bgTexture, NULL, &PBState->bgRect);
        SDL_RenderCopy(PBState->renderer, Bar->barTexture, NULL, &Bar->barRect);
        for (int i = 0; i < BUTTON_COUNT_MENU; i++)
        {
            showButton(PBState->renderer, buttonArr[i]);
        }
        SDL_RenderPresent(PBState->renderer);
        SDL_Delay(1000 / 60);
    }
    SDL_RenderClear(PBState->renderer);
    SDL_SetCursor(PBState->arrowCursor);
    destroyMenu(buttonArr, PBState->bgTexture, Bar, PBState->bgMusic, exitSound);
}
