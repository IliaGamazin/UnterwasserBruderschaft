#include "header.h"
SDL_Texture* bgTexture;
SDL_Rect bgRect;
Mix_Chunk* exitSound;
int menu(SDL_Renderer* renderer, SDL_Event event, SDL_Cursor* arrowCursor, SDL_Cursor* handCursor, Mix_Music* bgMusic){
    bool quitTimeFlag = false;
    int quitButtonSpeed = 1;
    int run = 0;
    
    bgTexture = IMG_LoadTexture(renderer, "media/img/menu_bg.png");
    bgRect = createRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_QueryTexture(bgTexture, NULL, NULL, &bgRect.w, &bgRect.h);

    int volume = MAX_VOLUME / 2;
    bgMusic = Mix_LoadMUS("media/sound/nightcall.mp3");
    Mix_PlayMusic(bgMusic, 0);

    Button* buttonArr = fillButtonArr((WINDOW_WIDTH - BUTTON_WIDTH) - 17, BUTTON_GAP * 1.5, BUTTON_WIDTH, BUTTON_HEIGHT, renderer);
    SoundBar* Bar = createSoundBar(185, 690, volume * 3, 30, renderer);
    while (run == 0) {
        while (SDL_PollEvent(&event)) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            SDL_Point mousePoint = { mouseX, mouseY };
            if (!quitTimeFlag)
            {
                handleButtonPointing(mousePoint, buttonArr, renderer, arrowCursor, handCursor);
            }
            if (event.type == SDL_QUIT) {
                run = -1;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                for (int i = 0; i < BUTTON_COUNT; i++)
                {
                    if (SDL_PointInRect(&mousePoint, &buttonArr[i].buttonRect) == true) {
                        switch (i)
                        {
                        case START_BUTTON:
                            run = INTRO;
                            printf("\nStart button");
                            break;
                        case FIRST_LEVEL_BUTTON:
                            printf("\nFirst level");
                            run = LEVEL1;
                            break;
                        case SECOND_LEVEL_BUTTON:
                            printf("\nSecond level");
                            run = LEVEL2;
                            break;
                        case THIRD_LEVEL_BUTTON:
                            printf("\nThird level");
                            run = LEVEL3;
                            break;
                        case EXIT_BUTTON:
                            if (!quitTimeFlag)
                            {
                                printf("\nExit button");
                                exitSound = Mix_LoadWAV("media/sound/carPass.wav");
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
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_EQUALS:
                    printf("\n Volume: %d", volume);
                    if (volume < MAX_VOLUME) {
                        volume += MAX_VOLUME / 10;
                    }
                    else {
                        volume = MAX_VOLUME;
                    }
                    break;
                case SDLK_MINUS:
                    printf("\n Volume: %d", volume);
                    if (volume > 0) {
                        volume -= MAX_VOLUME/10;
                    }
                    else {
                        volume = 0;
                    }
                    break;
                }
                
                Mix_Volume(-1, volume);
                Mix_VolumeMusic(volume);
            }
        }
        if (quitTimeFlag == true)
        {
            buttonArr[BUTTON_COUNT - 1].buttonRect.x -= quitButtonSpeed;
            quitButtonSpeed += 1;
            if (buttonArr[BUTTON_COUNT - 1].buttonRect.x < -BUTTON_WIDTH)
            {
                run = -1;
            }
        }
        updateSoundBar(Bar, volume);
        SDL_RenderCopy(renderer, bgTexture, NULL, &bgRect);
        SDL_RenderCopy(renderer, Bar->barTexture, NULL, &Bar->barRect);
        for (int i = 0; i < BUTTON_COUNT; i++)
        {
            showButton(renderer, buttonArr[i]);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 60);
    }
    SDL_RenderClear(renderer);
    destroyMenu(buttonArr, bgTexture, Bar, bgMusic, exitSound);
    return run;
}
