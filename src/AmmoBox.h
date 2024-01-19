#include "Libs.h"

// AmmoBox

typedef struct{
    SDL_Rect rect;
    SDL_Texture *full_tex;
    SDL_Texture *empty_tex;
    Mix_Chunk *reload_sound;
    bool is_full;
}AmmoBox;

AmmoBox AmmoBox_new(SDL_Renderer *r,int x, int y);
void AmmoBox_render(SDL_Renderer *r,AmmoBox box);
void AmmoBox_destroy(AmmoBox box);
