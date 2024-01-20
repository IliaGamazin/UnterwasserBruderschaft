#include "Libs.h"
enum TILE_TYPE{
    WALL,
    OBSTACLE,
    FLOOR
};
// Tilemap

typedef struct{
    SDL_Rect tile_rect;
    int tile_type;
}Tile;

typedef struct{
    Tile **tile_arr;
    SDL_Texture **tex_arr;
    SDL_Texture *bg_texture;
    SDL_Rect bg_rect;
}Tilemap;

Tilemap Map_new(SDL_Renderer *r);
void Map_render(Tilemap t, SDL_Renderer *r);
void Map_destroy(Tilemap t);