#include "Tilemap.h"

Tilemap createMap(SDL_Renderer* r){
    Tilemap Map;
    Map.tileArr = (Tile*)malloc(TILES_COUNT* sizeof(Tile));
    Map.texArr = (SDL_Texture**)malloc(TILES_TEXTURE_COUNT * sizeof(SDL_Texture*));
    Map.texArr[WALL_HORIZONTAL] = IMG_LoadTexture(r, "media/img/tiles/wall_horizontal.png");
    Map.texArr[WALL_VERTICAL] = IMG_LoadTexture(r, "media/img/tiles/wall_vertical.png");
    Map.texArr[FLOOR_WOOD] = IMG_LoadTexture(r, "media/img/tiles/floor_wood.png");
    Map.texArr[FLOOR_MARBLE] = IMG_LoadTexture(r, "media/img/tiles/floor_wood.png");
    int tileX = 0;
    int tileY = 0;
    for (int i = 0; i < TILES_COUNT; i++)
    {
        Map.tileArr[i].tileRect = createRect(tileX, tileY, TILE_SIZE, TILE_SIZE);
        if (tileY == 0 || tileY == WINDOW_HEIGHT-TILE_SIZE)
        {
            Map.tileArr[i].tileType = WALL_HORIZONTAL;
        }
        else if(tileX == 0 || tileX == WINDOW_WIDTH-TILE_SIZE){
            Map.tileArr[i].tileType = WALL_VERTICAL;
        }
        else{
            Map.tileArr[i].tileType = FLOOR_WOOD;
        }
        tileX += TILE_SIZE;
        if (tileX == WINDOW_WIDTH)
        {
            tileX = 0;
            tileY += TILE_SIZE;
        } 
    }
    return Map;
}
void showMap(Tilemap t, SDL_Renderer* r){
    for (int i = 0; i < TILES_COUNT; i++)
    {
        SDL_RenderCopy(r, t.texArr[t.tileArr[i].tileType], NULL, &t.tileArr[i].tileRect);
    }
}
void destroyMap(Tilemap t){
    for (int i = 0; i < TILES_TEXTURE_COUNT; i++)
    {
        SDL_DestroyTexture(t.texArr[i]);
    } 
    free(t.tileArr);
    free(t.texArr);
}