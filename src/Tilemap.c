#include "Tilemap.h"

// Tilemap

Tilemap Map_new(SDL_Renderer *r){
    Tilemap Map;
    Map.map_width = 48;
    Map.map_height = 27;
    Map.bg_rect = createRect(0, 0, LEVEL_WIDTH, LEVEL_HEIGHT);
    Map.tile_arr = (Tile**)malloc(48 * sizeof(Tile*));
    for (int i = 0; i < 48; i++) {
        Map.tile_arr[i] = (Tile*)malloc(27 * sizeof(Tile));
    }

    Map.bg_texture = IMG_LoadTexture(r, "media/img/tiles/bg.png");
    Map.tex_arr = (SDL_Texture**)malloc(3 * sizeof(SDL_Texture*));
    Map.tex_arr[WALL] = IMG_LoadTexture(r, "media/img/tiles/wall.png");
    Map.tex_arr[OBSTACLE] = IMG_LoadTexture(r, "media/img/tiles/obstacle.png");
    Map.tex_arr[FLOOR] = IMG_LoadTexture(r, "media/img/tiles/floor.png");
    for (int i = 0; i < Map.map_width; i++)
    {
       for (int j = 0; j < Map.map_height; j++)
       {
            Map.tile_arr[i][j].tile_rect = createRect(i*40, j*40, 40,40);
            if (((i == 0 || i == 47) && j < 48)||(i == 22 && (j >= 1 && j <=6)))
            {
                Map.tile_arr[i][j].tile_type = WALL;
            }
            else if (i == 15 && (j >= 4 && j< 12))
            {
                Map.tile_arr[i][j].tile_type = WALL;
            }
            else if(i == 4 && (j>=4 && j <= 17)){
                Map.tile_arr[i][j].tile_type = WALL;
            }
            
            else if((j == 3 && ((i >= 4 && i <= 15)|| (i>= 18 && i <= 21)))||(j == 0 &&(i >= 22 && i <= 34)) 
            | (j == 7 &&(( i >= 16 && i <= 18) || (i >= 21 && i <=26)))){
                Map.tile_arr[i][j].tile_type = WALL;
            }
            else if(j == 6 && (i>=5 && i <= 14)){
                Map.tile_arr[i][j].tile_type = OBSTACLE;
            }
            else if(j == 4 && (i>=26 && i <= 27)){
                Map.tile_arr[i][j].tile_type = OBSTACLE;
            }
            else{
                Map.tile_arr[i][j].tile_type = FLOOR;
            }
       }
    }
    return Map;
}
void Map_render(Tilemap t, SDL_Renderer* r){
    SDL_RenderCopy(r, t.bg_texture, NULL, &t.bg_rect);
    for (int i = 0; i < t.map_width; i++)
    {
        for (int j = 0; j < t.map_height; j++)
        {
            SDL_RenderCopy(r, t.tex_arr[t.tile_arr[i][j].tile_type], NULL, &t.tile_arr[i][j].tile_rect);
        }
    }
}
void Map_destroy(Tilemap t){
    for (int i = 0; i < 3; i++)
    {
        SDL_DestroyTexture(t.tex_arr[i]);
    } 
    for (int i = 0; i < t.map_width; i++)
    {
        free(t.tile_arr[i]);
    }
    SDL_DestroyTexture(t.bg_texture);
    free(t.tile_arr);
    free(t.tex_arr);
}