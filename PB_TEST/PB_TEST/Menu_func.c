#include "header.h"
SDL_Rect createRect(int x, int y, int rectWidth, int rectHeight) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = rectWidth;
    rect.h = rectHeight;
    return rect;
}
Button createButton(int x, int y, int buttonWidth, int buttonHeight, SDL_Texture* buttonTexIdle, SDL_Texture* buttonTexHover, Mix_Chunk* buttonSound) {
    Button But;
    But.buttonRect = createRect(x, y, buttonWidth, buttonHeight);
    But.buttonTexIdle = buttonTexIdle;
    But.buttonTexHover = buttonTexHover;
    But.buttonSound = buttonSound;
    But.isPointedAt = false;
    return But;
}
Button* fillButtonArr(int x, int y, int buttonWidth, int buttonHeight, SDL_Renderer* r) {
    Button* buttonArr = (Button*)malloc(BUTTON_COUNT * sizeof(Button));
    int incY = y;
    char pathIdle[20];
    char pathHover[20];
    for (int i = 0; i < BUTTON_COUNT - 1; i++)
    {
        sprintf_s(pathIdle, sizeof(pathIdle), "media/img/%d.png", i);
        sprintf_s(pathHover, sizeof(pathHover), "media/img/%d.png", i + 10);
        buttonArr[i] = createButton(x, incY, buttonWidth, buttonHeight, IMG_LoadTexture(r, pathIdle), IMG_LoadTexture(r, pathHover), Mix_LoadWAV("media/sound/pointSound.wav"));
        incY += BUTTON_GAP;
    }
    buttonArr[BUTTON_COUNT - 1] = createButton(x, incY, buttonWidth, buttonHeight, IMG_LoadTexture(r, "media/img/chevy_idle.png"), IMG_LoadTexture(r, "media/img/chevy_start.png"), Mix_LoadWAV("media/sound/carIgnition.wav"));
    return buttonArr;
}
void showButton(SDL_Renderer* r, Button button) {
    if (button.isPointedAt) {
        SDL_RenderCopy(r, button.buttonTexHover, NULL, &button.buttonRect);
    }
    else {
        SDL_RenderCopy(r, button.buttonTexIdle, NULL, &button.buttonRect);
    }
}
void handleButtonPointing(SDL_Point mousePoint, Button* buttonArr, SDL_Renderer* r, SDL_Cursor* arrowCursor, SDL_Cursor* handCursor) {
    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        if (SDL_PointInRect(&mousePoint, &buttonArr[i].buttonRect) == true) {
            SDL_SetCursor(handCursor);
            buttonArr[i].isPointedAt = true;
            break;
        }
        else {
            SDL_SetCursor(arrowCursor);
            buttonArr[i].isPointedAt = false;
            buttonArr[i].isPlayingSound = false;
        }
    }
    for (int i = 0; i < BUTTON_COUNT - 1; i++)
    {
        if (buttonArr[i].isPointedAt) {
            if (!buttonArr[i].isPlayingSound)
            {
                Mix_PlayChannel(-1, buttonArr[i].buttonSound, 0);
                buttonArr[i].isPlayingSound = true;
            }
            buttonArr[i].buttonRect.x = WINDOW_WIDTH - BUTTON_WIDTH - 22;
            buttonArr[i].buttonRect.w = BUTTON_WIDTH + 10;
            buttonArr[i].buttonRect.h = BUTTON_HEIGHT + 2;
            break;
        }
        else {
            buttonArr[i].buttonRect.x = WINDOW_WIDTH - BUTTON_WIDTH - 17;
            buttonArr[i].buttonRect.w = BUTTON_WIDTH;
            buttonArr[i].buttonRect.h = BUTTON_HEIGHT;
            buttonArr[i].isPlayingSound = false;
        }
    }
    if (buttonArr[BUTTON_COUNT - 1].isPointedAt)
    {
        if (!buttonArr[BUTTON_COUNT - 1].isPlayingSound)
        {
            Mix_PlayChannel(-1, buttonArr[BUTTON_COUNT - 1].buttonSound, 0);
            buttonArr[BUTTON_COUNT - 1].isPlayingSound = true;
        }
    }
}
SoundBar* createSoundBar(int x, int y, int barWidth, int barHeight, SDL_Renderer* r) {
    SoundBar* Bar = (SoundBar*)malloc(sizeof(SoundBar));
    Bar->barRect = createRect(x, y, barWidth, barHeight);
    Bar->barTexture = IMG_LoadTexture(r, "media/img/soundbar.png");
    return Bar;
}
void updateSoundBar(SoundBar* soundBar, int volume) {
    soundBar->barRect.w = volume * 3;
}
void destroyButton(Button b) {
    SDL_DestroyTexture(b.buttonTexIdle);
    SDL_DestroyTexture(b.buttonTexHover);
    Mix_FreeChunk(b.buttonSound);
}
void destroyBar(SoundBar* b) {
    SDL_DestroyTexture(b->barTexture);
    free(b);
}
void destroyMenu(Button* buttonArr, SDL_Texture* bgTexture, SoundBar* Bar, Mix_Music* bgMusic, Mix_Chunk* exitSound) {
    SDL_DestroyTexture(bgTexture);
    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        destroyButton(buttonArr[i]);
    }
    Mix_FreeChunk(exitSound);
    Mix_FreeMusic(bgMusic);
    destroyBar(Bar);
    free(buttonArr);
}
void destroyWindow(SDL_Renderer* r, SDL_Window* window, SDL_Cursor* arrow, SDL_Cursor* hand) {
    SDL_DestroyRenderer(r);
    SDL_FreeCursor(arrow);
    SDL_FreeCursor(hand);
    SDL_DestroyWindow(window);
    Mix_Quit();
    SDL_Quit();
}