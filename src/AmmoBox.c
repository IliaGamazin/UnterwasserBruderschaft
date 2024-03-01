#include "../inc/AmmoBox.h"
#include "../inc/Entity.h"

AmmoBox *AmmoBox_new(SDL_Renderer *r, int x, int y) {
    AmmoBox *box = malloc(sizeof(AmmoBox));
    
    box->rect = Rect_new(x, y, TILE_SIZE * 2, TILE_SIZE);
    box->full_tex = IMG_LoadTexture(r, "./resource/img/ammobox_full.png");
    box->empty_tex = IMG_LoadTexture(r, "./resource/img/ammobox_empty.png");
    box->reload_sound = Mix_LoadWAV("./resource/sound/reloadbox_sound.wav");

    box->is_full = true;
    return box;
}

void AmmoBox_update(AmmoBox *box, Entity *player) {
    if (box->is_full && SDL_HasIntersection(&box->rect, &player->rect)) {
        box->is_full = false;
        player->weapon->ammo = player->weapon->ammo_max;
    }
}

void AmmoBox_render(SDL_Renderer *renderer, AmmoBox *box, Tilemap *map) {
    SDL_SetRenderTarget(renderer, map->render_texture);
    SDL_RenderCopy(
        renderer,
        (box->is_full ? box->full_tex : box->empty_tex),
        NULL,
        &box->rect
    );
    SDL_SetRenderTarget(renderer, NULL);
}

void AmmoBox_destroy(AmmoBox *box) {
    SDL_DestroyTexture(box->empty_tex);
    SDL_DestroyTexture(box->full_tex);
    Mix_FreeChunk(box->reload_sound);
    free(box);
}

