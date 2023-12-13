#include "header.h"
SDL_Rect createRect(int x, int y, int rectWidth, int rectHeight) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = rectWidth;
    rect.h = rectHeight;
    return rect;
}
Button createButton(int x, int y, int buttonWidth, int buttonHeight, SDL_Texture* buttonTex, Mix_Chunk* buttonSound) {
    Button But;
    But.buttonRect = createRect(x, y, buttonWidth, buttonHeight);
    But.isPointedAt = false;
    But.buttonTexture = buttonTex;
    But.buttonSound = buttonSound;
    return But;
}
Button* fillButtonArr(int x, int y, int buttonWidth, int buttonHeight, SDL_Renderer* renderer) {
    Button* buttons = (Button*)malloc(BUTTON_COUNT * sizeof(Button));
    int incY = y;
    for (int i = 0; i < BUTTON_COUNT; i++)
    {
       
        buttons[i] = createButton(x, incY, buttonWidth, buttonHeight, NULL, NULL);
        incY += BUTTON_GAP;
    }
    return buttons;
}
void showButton(SDL_Renderer* r, Button myButton) {
    SDL_RenderCopy(r, myButton.buttonTexture, NULL, &myButton.buttonRect);
}
void handleButtonPointing(SDL_Point mousePoint, Button* buttonArr, SDL_Renderer* renderer) {
    char path[20];
    bool isCursorInsideButton = false;
    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        if (SDL_PointInRect(&mousePoint, &buttonArr[i].buttonRect) == true) {
            buttonArr[i].isPointedAt = true;
            
            isCursorInsideButton = true;
            break;
        }
        else {
            buttonArr[i].isPointedAt = false;
            buttonArr[i].isPlayingSound = false;
        }
    }
    for (int i = 0; i < BUTTON_COUNT - 1; i++)
    {
        if (buttonArr[i].isPointedAt) {
            sprintf_s(path, sizeof(path), "media/img/%d.jpg", i + 10);
            buttonArr[i].buttonSound = (Mix_LoadWAV("media/sound/pointSound.wav"));
            if (!buttonArr[i].isPlayingSound)
            {
                Mix_PlayChannel(-1, buttonArr[i].buttonSound, 0);
                buttonArr[i].isPlayingSound = true;
            }
           
            buttonArr[i].buttonTexture = IMG_LoadTexture(renderer, path);
            buttonArr[i].buttonRect.w = BUTTON_WIDTH + 10;
            buttonArr[i].buttonRect.h = BUTTON_HEIGHT + 2;
            buttonArr[i].buttonRect.x = (WINDOW_WIDTH - BUTTON_WIDTH) - 15;
            break;
        }
        else {
            sprintf_s(path, sizeof(path), "media/img/%d.jpg", i);
            buttonArr[i].isPlayingSound = false;
            buttonArr[i].buttonTexture = IMG_LoadTexture(renderer, path);
            buttonArr[i].buttonRect.w = BUTTON_WIDTH;
            buttonArr[i].buttonRect.h = BUTTON_HEIGHT;
            buttonArr[i].buttonRect.x = (WINDOW_WIDTH - BUTTON_WIDTH)-10;
        }
    }
    if (buttonArr[BUTTON_COUNT-1].isPointedAt)
    {
        buttonArr[BUTTON_COUNT - 1].buttonTexture = IMG_LoadTexture(renderer, "media/img/chevy_start.png");
        buttonArr[BUTTON_COUNT - 1].buttonSound = (Mix_LoadWAV("media/sound/carIgnition.wav"));
        if (!buttonArr[BUTTON_COUNT - 1].isPlayingSound)
        {
            Mix_PlayChannel(-1, buttonArr[BUTTON_COUNT - 1].buttonSound, 0);
            buttonArr[BUTTON_COUNT - 1].isPlayingSound = true;
        }
    }
    else {
        buttonArr[BUTTON_COUNT - 1].buttonTexture = IMG_LoadTexture(renderer, "media/img/chevy_idle.png");
    }
    if (isCursorInsideButton) {
        SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
    }
    else {
        SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
    }
}

void close(SDL_Renderer* renderer, SDL_Window* window, Button* buttonArr, SDL_Texture* bgTexture) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(bgTexture);
    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        SDL_DestroyTexture(buttonArr[i].buttonTexture);
        Mix_FreeChunk(buttonArr[i].buttonSound);
    }
    free(buttonArr);
    SDL_DestroyWindow(window);
    Mix_Quit();
    SDL_Quit();
}