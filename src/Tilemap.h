#include "Libs.h"

typedef struct{
    SDL_Rect tileRect;
    int tileType;
}Tile;

typedef struct{
    Tile* tileArr;
    SDL_Texture** texArr;
}Tilemap;

Tilemap createMap(SDL_Renderer* r);
void showMap(Tilemap t, SDL_Renderer* r);
void destroyMap(Tilemap t);