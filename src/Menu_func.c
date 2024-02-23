#include "../include/Header_main.h"

SDL_Rect Rect_new(int x, int y, int w, int h) {
    return (SDL_Rect) {
        x,
        y,
        w,
        h,
    };
}

void handle_pointing_menu(SDL_Point mouse_point, Button *button_arr, GameState *PBState) {
    for (int i = 0; i < BUTTON_COUNT_MENU; i++) {
        if (SDL_PointInRect(&mouse_point, &button_arr[i].button_rect)) {
            SDL_SetCursor(PBState->handCursor);
            button_arr[i].hower = true;
            break;
        }
        else {
            SDL_SetCursor(PBState->arrowCursor);
            button_arr[i].hower = false;
            button_arr[i].playing_sound = false;
        }
    }

    for (int i = 0; i < BUTTON_COUNT_MENU - 1; i++) {
        if (button_arr[i].hower) {
            if (!button_arr[i].playing_sound) {
                Mix_PlayChannel(-1, button_arr[i].button_sound, 0);
                button_arr[i].playing_sound = true;
            }

            button_arr[i].button_rect.x = WINDOW_WIDTH - BUTTON_WIDTH - 22;
            button_arr[i].button_rect.w = BUTTON_WIDTH + 10;
            button_arr[i].button_rect.h = BUTTON_HEIGHT + 2;

            break;
        }
        else {
            button_arr[i].button_rect.x = WINDOW_WIDTH - BUTTON_WIDTH - 17;
            button_arr[i].button_rect.w = BUTTON_WIDTH;
            button_arr[i].button_rect.h = BUTTON_HEIGHT;
            button_arr[i].playing_sound = false;
        }
    }
    
    if (button_arr[BUTTON_COUNT_MENU - 1].hower) {
        if (!button_arr[BUTTON_COUNT_MENU - 1].playing_sound) {
            Mix_PlayChannel(-1, button_arr[BUTTON_COUNT_MENU - 1].button_sound, 0);
            button_arr[BUTTON_COUNT_MENU - 1].playing_sound = true;
        }
    }
}

void destroyMenu(Button* buttonArr, SDL_Texture* bgTexture, SoundBar* Bar, Mix_Music* bgMusic, Mix_Chunk* exitSound) {
    SDL_DestroyTexture(bgTexture);
    for (int i = 0; i < BUTTON_COUNT_MENU; i++) {
        Button_destroy(buttonArr[i]);
    }
    Mix_FreeChunk(exitSound);
    Mix_FreeMusic(bgMusic);
    SoundBar_destroy(Bar);
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

