#include "SoundBar.h"

SoundBar* createSoundBar(int x, int y, int barWidth, int barHeight, SDL_Renderer* r) {
    SoundBar* Bar = (SoundBar*)malloc(sizeof(SoundBar));
    Bar->barRect = createRect(x, y, barWidth, barHeight);
    Bar->barTexture = IMG_LoadTexture(r, "media/img/soundbar.png");
    return Bar;
}

void updateSoundBar(SoundBar* soundBar, int volume) {
    soundBar->barRect.w = volume * 3;
}
void destroyBar(SoundBar* b) {
    SDL_DestroyTexture(b->barTexture);
    free(b);
}