#include "../include/AmmoBox.h"
#include "../include/Camera.h"

AmmoBox AmmoBox_new(SDL_Renderer *r, int x, int y) {
    return (AmmoBox) {
        Rect_new(x, y, TILE_SIZE * 2, TILE_SIZE),
        IMG_LoadTexture(r, "./media/img/ammobox_full.png"),
        IMG_LoadTexture(r, "./media/img/ammobox_empty.png"),
        Mix_LoadWAV("./media/sound/reloadbox_sound.wav"),
        true,
    };
}

void AmmoBox_render(SDL_Renderer *r, AmmoBox box, Camera camera) {
    SDL_Rect renderQuad = {
        box.rect.x - camera.position.x,
        box.rect.y - camera.position.y,
        box.rect.w,
        box.rect.h
    };

    // Render the correct texture based on whether the box is full or empty

    SDL_RenderCopy(r, (box.is_full ? box.full_tex : box.empty_tex), NULL, &renderQuad);
}

void AmmoBox_destroy(AmmoBox box) {
    SDL_DestroyTexture(box.empty_tex);
    SDL_DestroyTexture(box.full_tex);
    Mix_FreeChunk(box.reload_sound);
}

