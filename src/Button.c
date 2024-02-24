#include "../inc/Button.h"

// Button

Button Button_new(int x, int y, int w, int h, SDL_Texture *button_tex_idle, SDL_Texture *button_tex_hover, Mix_Chunk *button_sound ) {
    return (Button) {
        Rect_new(x, y, w, h),
        button_tex_idle,
        button_tex_hover,
        button_sound,
        false,
        false,
    };
}

Button *Button_arr_new_menu(int x, int y, int w, int h, SDL_Renderer *r) {
    Button *button_arr = (Button*)malloc(BUTTON_COUNT_MENU * sizeof(Button));

    int incY = y;
    char path_idle[30];
    char path_hover[30];

    for (int i = 0; i < BUTTON_COUNT_MENU - 1; i++) {
        sprintf(path_idle, "media/img/menu/%d.png", i);
        sprintf(path_hover, "media/img/menu/%d.png", i + 10);
        button_arr[i] = Button_new(x, incY, w, h, IMG_LoadTexture(r, path_idle), IMG_LoadTexture(r, path_hover), Mix_LoadWAV("media/sound/pointSound.wav"));
        incY += BUTTON_GAP;
    }

    button_arr[BUTTON_COUNT_MENU - 1] = Button_new(x, incY, w, h, IMG_LoadTexture(r, "media/img/menu/chevy_idle.png"), IMG_LoadTexture(r, "media/img/menu/chevy_start.png"), Mix_LoadWAV("media/sound/carIgnition.wav"));
    return button_arr;
}

Button *Button_arr_new_choose(SDL_Renderer *r) {
    Button *ButtonArr = (Button*)malloc(3 * sizeof(Button));

    ButtonArr[0] = Button_new(290, 180, 175, 520, IMG_LoadTexture(r, "media/img/chooseHero/shaButton.png"), IMG_LoadTexture(r, "media/img/chooseHero/shaButtonAct.png"), Mix_LoadWAV("media/sound/ShayluButton.wav"));
    ButtonArr[1] = Button_new(555, 180, 175, 520, IMG_LoadTexture(r, "media/img/chooseHero/yalButton.png"), IMG_LoadTexture(r, "media/img/chooseHero/yalButtonAct.png"), Mix_LoadWAV("media/sound/YaltButton.wav"));
    ButtonArr[2] = Button_new(820, 180, 175, 520, IMG_LoadTexture(r, "media/img/chooseHero/dawButton.png"), IMG_LoadTexture(r, "media/img/chooseHero/dawButtonAct.png"), Mix_LoadWAV("media/sound/DawButton.wav"));

    return ButtonArr;
}

void Button_render(SDL_Renderer *r, Button button) {
    if (button.hower) {
        SDL_RenderCopy(r, button.button_tex_hover, NULL, &button.button_rect);
    }
    else {
        SDL_RenderCopy(r, button.button_tex_idle, NULL, &button.button_rect);
    }
}

void Button_destroy(Button b) {
    SDL_DestroyTexture(b.button_tex_idle);
    SDL_DestroyTexture(b.button_tex_hover);
    Mix_FreeChunk(b.button_sound);
}

