#include "../include/SoundBar.h"

SoundBar *SoundBar_new(SDL_Renderer *renderer, int x, int y, int w, int h) {
    SoundBar* Bar = malloc(sizeof(SoundBar));

    Bar->rect = Rect_new(x, y, w, h);
    Bar->texture = IMG_LoadTexture(renderer, "./media/img/hud/soundbar.png");

    return Bar;
}

void SoundBar_update(SoundBar *bar, int volume) {
    bar->rect.w = volume * 3;
}

void SoundBar_destroy(SoundBar *bar) {
    SDL_DestroyTexture(bar->texture);
    free(bar);
}

