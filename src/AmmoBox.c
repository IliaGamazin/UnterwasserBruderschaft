#include "AmmoBox.h"
#include "Camera.h"

AmmoBox AmmoBox_new(SDL_Renderer *r, int x, int y) {
    AmmoBox box;
    box.rect = createRect(x, y, TILE_SIZE * 2, TILE_SIZE);
    box.empty_tex = IMG_LoadTexture(r, "media/img/ammobox_empty.png");
    box.full_tex = IMG_LoadTexture(r, "media/img/ammobox_full.png");
    box.is_full = true;
    box.reload_sound = Mix_LoadWAV("media/sound/reloadbox_sound.wav");
    return box;
}

void AmmoBox_render(SDL_Renderer *r, AmmoBox box, Camera camera) {
   
    SDL_Rect renderQuad = {
        box.rect.x - camera.position.x,
        box.rect.y - camera.position.y,
        box.rect.w,
        box.rect.h
    };

    // Render the correct texture based on whether the box is full or empty
    if (box.is_full) {
        SDL_RenderCopy(r, box.full_tex, NULL, &renderQuad);
    } else {
        SDL_RenderCopy(r, box.empty_tex, NULL, &renderQuad);
    }
}

void AmmoBox_destroy(AmmoBox box) {
    SDL_DestroyTexture(box.empty_tex);
    SDL_DestroyTexture(box.full_tex);
    Mix_FreeChunk(box.reload_sound);
}








