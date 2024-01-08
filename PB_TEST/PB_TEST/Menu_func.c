#include "Header_main.h"
SDL_Rect createRect(int x, int y, int rectWidth, int rectHeight) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = rectWidth;
    rect.h = rectHeight;
    return rect;
}

void handleButtonPointingMenu(SDL_Point mousePoint, Button* buttonArr, GameState* PBState) {
    for (int i = 0; i < BUTTON_COUNT_MENU; i++)
    {
        if (SDL_PointInRect(&mousePoint, &buttonArr[i].buttonRect) == true) {
            SDL_SetCursor(PBState->handCursor);
            buttonArr[i].isPointedAt = true;
            break;
        }
        else {
            SDL_SetCursor(PBState->arrowCursor);
            buttonArr[i].isPointedAt = false;
            buttonArr[i].isPlayingSound = false;
        }
    }
    for (int i = 0; i < BUTTON_COUNT_MENU - 1; i++)
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
    if (buttonArr[BUTTON_COUNT_MENU - 1].isPointedAt)
    {
        if (!buttonArr[BUTTON_COUNT_MENU - 1].isPlayingSound)
        {
            Mix_PlayChannel(-1, buttonArr[BUTTON_COUNT_MENU - 1].buttonSound, 0);
            buttonArr[BUTTON_COUNT_MENU - 1].isPlayingSound = true;
        }
    }
}

void destroyMenu(Button* buttonArr, SDL_Texture* bgTexture, SoundBar* Bar, Mix_Music* bgMusic, Mix_Chunk* exitSound) {
    SDL_DestroyTexture(bgTexture);
    for (int i = 0; i < BUTTON_COUNT_MENU; i++)
    {
        destroyButton(buttonArr[i]);
    }
    Mix_FreeChunk(exitSound);
    Mix_FreeMusic(bgMusic);
    destroyBar(Bar);
    free(buttonArr);
}
void destroyWindow(GameState* PB, SDL_Window* window ) {
    SDL_DestroyRenderer(PB->renderer);
    SDL_FreeCursor(PB->arrowCursor);
    SDL_FreeCursor(PB->handCursor);
    free(PB);
    SDL_DestroyWindow(window);
    Mix_Quit();
    SDL_Quit();
}