#include "Tilemap.h"

// Tilemap

Tilemap Map_new(SDL_Renderer *r){
    Tilemap Map;

    Map.width = 48;
    Map.height = 27;
    Map.bg_rect = createRect(0, 0, LEVEL_WIDTH, LEVEL_HEIGHT);
    Map.tiles = malloc(sizeof(Tile *) * 48);

    for (int i = 0; i < 48; i++) {
        Map.tiles[i] = malloc(sizeof(Tile) * 27);
    }

    Map.bg_texture = IMG_LoadTexture(r, "media/img/tiles/bg.png");
    Map.textures = malloc(sizeof(SDL_Texture *) * 3);
    Map.textures[WALL] = IMG_LoadTexture(r, "media/img/tiles/wall.png");
    Map.textures[OBSTACLE] = IMG_LoadTexture(r, "media/img/tiles/obstacle.png");
    Map.textures[FLOOR] = IMG_LoadTexture(r, "media/img/tiles/floor.png");

    for (int i = 0; i < Map.width; i++)
    {
       for (int j = 0; j < Map.height; j++)
       {
            Map.tiles[i][j].tile_rect = createRect(i*40, j*40, 40,40);
            if (((i == 0 || i == 47) && j < 48)||(i == 22 && (j >= 1 && j <=6)))
            {
                Map.tiles[i][j].type = WALL;
            }
            else if (i == 15 && (j >= 4 && j< 12))
            {
                Map.tiles[i][j].type = WALL;
            }
            else if(i == 4 && (j>=4 && j <= 17)){
                Map.tiles[i][j].type = WALL;
            }
            
            else if((j == 3 && ((i >= 4 && i <= 15)|| (i>= 18 && i <= 21)))||(j == 0 &&(i >= 22 && i <= 34)) 
            | (j == 7 &&(( i >= 16 && i <= 18) || (i >= 21 && i <=26)))){
                Map.tiles[i][j].type = WALL;
            }
            else if(j == 6 && (i>=5 && i <= 14)){
                Map.tiles[i][j].type = OBSTACLE;
            }
            else if(j == 4 && (i>=26 && i <= 27)){
                Map.tiles[i][j].type = OBSTACLE;
            }
            else{
                Map.tiles[i][j].type = FLOOR;
            }
       }
    }
    return Map;
}
void Map_render(Tilemap t, SDL_Renderer* r){
    SDL_RenderCopy(r, t.bg_texture, NULL, &t.bg_rect);
    for (int i = 0; i < t.width; i++)
    {
        for (int j = 0; j < t.height; j++)
        {
            SDL_RenderCopy(r, t.textures[t.tiles[i][j].type], NULL, &t.tiles[i][j].tile_rect);
        }
    }
}
void Map_destroy(Tilemap t){
    for (int i = 0; i < 3; i++)
    {
        SDL_DestroyTexture(t.textures[i]);
    } 
    for (int i = 0; i < t.width; i++)
    {
        free(t.tiles[i]);
    }
    SDL_DestroyTexture(t.bg_texture);
    free(t.tiles);
    free(t.textures);
}

double Map_raycast(Tilemap map, Ray ray, TILE_TYPE type) {
    Vector2_scale(&ray.origin, 1.0 / TILE_SIZE);
    Vector2 position = ray.origin;

    int map_x = position.x - (ray.direction.x < 0);
    int map_y = position.y - (ray.direction.y < 0);

    while (map.tiles[map_x][map_y].type != type) {
        // Return -1 if out of bounds

        if ((map_x < 0 || map_x >= map.width) || (map_y < 0 || map_y >= map.height)) {
            return -1;
        }

        // Ray casting

        Vector2 deltas = Vector2_new(5, 5);

        if (ray.direction.x) {
            deltas.x = (ray.direction.x < 0 ? ceil(position.x - 1) : floor(position.x + 1)) - position.x;
        }

        if (ray.direction.y) {
            deltas.y = (ray.direction.y < 0 ? ceil(position.y - 1) : floor(position.y + 1)) - position.y;
        }

        Vector2 deltas_squared = Vector2_new(
            deltas.x * deltas.x,
            deltas.y * deltas.y
        );

        position = Vector2_add(
            position,
            (deltas_squared.x <= deltas_squared.y ?
             Vector2_scaled_to_x(ray.direction, deltas.x) :
             Vector2_scaled_to_y(ray.direction, deltas.y)
            )
        );

        map_x += (ray.direction.x < 0 ? -1 : 1) * (deltas_squared.x <= deltas_squared.y);
        map_y += (ray.direction.y < 0 ? -1 : 1) * (deltas_squared.y <= deltas_squared.x);
    }

    return Vector2_magnitude(Vector2_from_points(ray.origin, position)) * TILE_SIZE;
}

