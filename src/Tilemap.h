#include "Libs.h"

// Tilemap

typedef struct{
    SDL_Rect tile_rect;
    int tile_type;
}Tile;

typedef struct{
    Tile** tile_arr;
    SDL_Texture** tex_arr;
}Tilemap;

Tilemap Map_new(SDL_Renderer* r);
void Map_render(Tilemap t, SDL_Renderer* r);
void Map_destroy(Tilemap t);