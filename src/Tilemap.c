#include "Tilemap.h"

// Tilemap

Tilemap Map_new(SDL_Renderer* r){
    Tilemap Map;
    Map.tile_arr = (Tile**)malloc(48 * sizeof(Tile*));
    for (int i = 0; i < 48; i++) {
        Map.tile_arr[i] = (Tile*)malloc(27 * sizeof(Tile));
    }
    Map.tex_arr = (SDL_Texture**)malloc(TILES_TEXTURE_COUNT * sizeof(SDL_Texture*));
    Map.tex_arr[WALL_HORIZONTAL] = IMG_LoadTexture(r, "media/img/tiles/wall_horizontal.png");
    Map.tex_arr[WALL_VERTICAL] = IMG_LoadTexture(r, "media/img/tiles/wall_vertical.png");
    Map.tex_arr[FLOOR_WOOD] = IMG_LoadTexture(r, "media/img/tiles/floor_wood.png");
    Map.tex_arr[FLOOR_MARBLE] = IMG_LoadTexture(r, "media/img/tiles/floor_marble.png");
    for (int i = 0; i < 48; i++)
    {
       for (int j = 0; j < 27; j++)
       {
            Map.tile_arr[i][j].tile_rect = createRect(i*40, j*40, 40,40);
            if (i == 0 || i == 47)
            {
                Map.tile_arr[i][j].tile_type = WALL_VERTICAL;
            }
            else if (i == 4 && (j >= 4 && j< 18))
            {
                Map.tile_arr[i][j].tile_type = WALL_VERTICAL;
            }

            else if (i == 15 && (j >= 4 && j< 12))
            {
                Map.tile_arr[i][j].tile_type = WALL_VERTICAL;
            }
            
            else if(j == 3 && (i >= 4 && i<=15)){
                Map.tile_arr[i][j].tile_type = WALL_HORIZONTAL;
            }
            else{
                Map.tile_arr[i][j].tile_type = FLOOR_WOOD;
            }
       }
    }
    return Map;
}
void Map_render(Tilemap t, SDL_Renderer* r){
    for (int i = 0; i < 48; i++)
    {
        for (int j = 0; j < 27; j++)
        {
            SDL_RenderCopy(r, t.tex_arr[t.tile_arr[i][j].tile_type], NULL, &t.tile_arr[i][j].tile_rect);
        }
    }
}
void Map_destroy(Tilemap t){
    for (int i = 0; i < TILES_TEXTURE_COUNT; i++)
    {
        SDL_DestroyTexture(t.tex_arr[i]);
    } 
    for (int i = 0; i < 48; i++)
    {
        free(t.tile_arr[i]);
    }
    
    free(t.tile_arr);
    free(t.tex_arr);
}