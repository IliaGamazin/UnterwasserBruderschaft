#include "./Button.h"

// Button

Button createButton(int x, int y, int buttonWidth, int buttonHeight, SDL_Texture* buttonTexIdle, SDL_Texture* buttonTexHover, Mix_Chunk* buttonSound) {
    Button But;
    But.buttonRect = createRect(x, y, buttonWidth, buttonHeight);
    But.buttonTexIdle = buttonTexIdle;
    But.buttonTexHover = buttonTexHover;
    But.buttonSound = buttonSound;
    But.isPointedAt = false;
    return But;
}
Button* fillButtonArrMenu(int x, int y, int buttonWidth, int buttonHeight, SDL_Renderer* r) {
    Button* buttonArr = (Button*)malloc(BUTTON_COUNT_MENU * sizeof(Button));
    int incY = y;
    char pathIdle[30];
    char pathHover[30];
    for (int i = 0; i < BUTTON_COUNT_MENU - 1; i++)
    {
        sprintf(pathIdle, "media/img/menu/%d.png", i);
        sprintf(pathHover, "media/img/menu/%d.png", i + 10);
        buttonArr[i] = createButton(x, incY, buttonWidth, buttonHeight, IMG_LoadTexture(r, pathIdle), IMG_LoadTexture(r, pathHover), Mix_LoadWAV("media/sound/pointSound.wav"));
        incY += BUTTON_GAP;
    }
    buttonArr[BUTTON_COUNT_MENU - 1] = createButton(x, incY, buttonWidth, buttonHeight, IMG_LoadTexture(r, "media/img/menu/chevy_idle.png"), IMG_LoadTexture(r, "media/img/menu/chevy_start.png"), Mix_LoadWAV("media/sound/carIgnition.wav"));
    return buttonArr;
}
Button* fillButtonArrChoose(SDL_Renderer* r) {
    Button* ButtonArr = (Button*)malloc(3 * sizeof(Button));
    ButtonArr[0] = createButton(290, 180, 175, 520, IMG_LoadTexture(r, "media/img/chooseHero/shaButton.png"), IMG_LoadTexture(r, "media/img/chooseHero/shaButtonAct.png"), Mix_LoadWAV("media/sound/ShayluButton.wav"));
    ButtonArr[1] = createButton(555, 180, 175, 520, IMG_LoadTexture(r, "media/img/chooseHero/yalButton.png"), IMG_LoadTexture(r, "media/img/chooseHero/yalButtonAct.png"), Mix_LoadWAV("media/sound/YaltButton.wav"));
    ButtonArr[2] = createButton(820, 180, 175, 520, IMG_LoadTexture(r, "media/img/chooseHero/dawButton.png"), IMG_LoadTexture(r, "media/img/chooseHero/dawButtonAct.png"), Mix_LoadWAV("media/sound/DawButton.wav"));
    return ButtonArr;
}

void showButton(SDL_Renderer* r, Button button) {
    if (button.isPointedAt) {
        SDL_RenderCopy(r, button.buttonTexHover, NULL, &button.buttonRect);
    }
    else {
        SDL_RenderCopy(r, button.buttonTexIdle, NULL, &button.buttonRect);
    }
}
void destroyButton(Button b) {
    SDL_DestroyTexture(b.buttonTexIdle);
    SDL_DestroyTexture(b.buttonTexHover);
    Mix_FreeChunk(b.buttonSound);
}

