#include "../inc/AmmoBox.h"

AmmoBox AmmoBox_new(SDL_Renderer *r, int x, int y) {
    return (AmmoBox) {
        Rect_new(x, y, TILE_SIZE * 2, TILE_SIZE),
        IMG_LoadTexture(r, "./resource/img/ammobox_full.png"),
        IMG_LoadTexture(r, "./resource/img/ammobox_empty.png"),
        Mix_LoadWAV("./resource/sound/reloadbox_sound.wav"),
        true,
    };
}

void AmmoBox_render(SDL_Renderer *renderer, AmmoBox box, Tilemap *map) {
    SDL_SetRenderTarget(renderer, map->render_texture);
    SDL_RenderCopy(
        renderer,
        (box.is_full ? box.full_tex : box.empty_tex),
        NULL,
        &box.rect
    );
    SDL_SetRenderTarget(renderer, NULL);
}

void AmmoBox_destroy(AmmoBox box) {
    SDL_DestroyTexture(box.empty_tex);
    SDL_DestroyTexture(box.full_tex);
    Mix_FreeChunk(box.reload_sound);
}

