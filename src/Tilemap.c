#include "../inc/Tilemap.h"
#include "../inc/Camera.h"

// Tilemap

Tilemap Map_new(SDL_Renderer *r) {
    Tilemap Map;

    Map.width = 48;
    Map.height = 27;
    Map.bg_rect = Rect_new(0, 0, LEVEL_WIDTH, LEVEL_HEIGHT);
    Map.tiles = malloc(sizeof(Tile *) * 48);

    for (int i = 0; i < 48; i++) {
        Map.tiles[i] = malloc(sizeof(Tile) * 27);
    }

    Map.bg_texture = IMG_LoadTexture(r, "./resource/img/tiles/bg.png");
    Map.textures = malloc(sizeof(SDL_Texture *) * 3);
    Map.textures[WALL] = IMG_LoadTexture(r, "./resource/img/tiles/wall.png");
    Map.textures[OBSTACLE] = IMG_LoadTexture(r, "./resource/img/tiles/obstacle.png");
    Map.textures[FLOOR] = IMG_LoadTexture(r, "./resource/img/tiles/floor.png");

    for (size_t i = 0; i < Map.width; i++)
    {
       for (size_t j = 0; j < Map.height; j++)
       {
            Map.tiles[i][j].tile_rect = Rect_new(i * 40, j * 40, 40, 40);
            if (i == 22 && (j >= 1 && j <= 6)) {
                Map.tiles[i][j].type = WALL;
            }
            else if ((i == 0 || i == 47) && j < 48) {
                Map.tiles[i][j].type = WALL;
            }
            else if (i == 4 && (j >= 4 && j <= 17)) {
                Map.tiles[i][j].type = WALL;
            }
            else if ((i >= 4 && i <= 23) && (j == 18)) {
                Map.tiles[i][j].type = WALL;
            }
            else if (((i >= 4 && i <= 15) || (i >= 18 && i <= 21)) && j == 3) {
                Map.tiles[i][j].type = WALL;
            }
            else if ((i >= 5 && i <= 14) && j == 6) {
                Map.tiles[i][j].type = OBSTACLE;
            }
            else if (i == 15 && (j >= 4 && j < 12)) {
                Map.tiles[i][j].type = WALL;
            }
            else if (i == 15 && (j >= 14 && j <= 18)) {
                Map.tiles[i][j].type = WALL;
            }
            else if (((i >= 16 && i <= 18) || (i >= 21 && i <= 26)) && j == 7) {
                Map.tiles[i][j].type = WALL;
            }
            else if ((i >= 22 && i <= 34) && j == 0) {
                Map.tiles[i][j].type = WALL;
            }
            else if ((i >= 26 && i <= 27) && j == 4) {
                Map.tiles[i][j].type = OBSTACLE;
            }
            else if ((i >= 27 && i <= 43) && j == 18) {
                Map.tiles[i][j].type = WALL;
            }
            else if ((i >= 30 && i <= 33) && j == 7) {
                Map.tiles[i][j].type = WALL;
            }
            else if (i == 34 && (j >= 1 && j <= 11)) {
                Map.tiles[i][j].type = WALL;
            }
            else if (i == 34 && (j >= 14 && j <= 17)) {
                Map.tiles[i][j].type = WALL;
            }
            else if ((i >= 35 && i <= 42) && j == 6) {
                Map.tiles[i][j].type = WALL;
            }
            else if (i == 43 && (j >= 6 && j <= 18)) {
                Map.tiles[i][j].type = WALL;
            }
            else {
                Map.tiles[i][j].type = FLOOR;
            }
       }
    }
    return Map;
}

void Map_render(Tilemap t, SDL_Renderer* r, Camera camera){
    // Move background rect according to camera
    SDL_Rect adjustedBgRect = {
        t.bg_rect.x - camera.position.x,
        t.bg_rect.y - camera.position.y,
        t.bg_rect.w,
        t.bg_rect.h
    };
    SDL_RenderCopy(r, t.bg_texture, NULL, &adjustedBgRect);

    // Render each tile cons camera
    for (size_t i = 0; i < t.width; i++) {
        for (size_t j = 0; j < t.height; j++) {
            SDL_Rect adjustedTileRect = {
                t.tiles[i][j].tile_rect.x - camera.position.x,
                t.tiles[i][j].tile_rect.y - camera.position.y,
                t.tiles[i][j].tile_rect.w,
                t.tiles[i][j].tile_rect.h
            };
            SDL_RenderCopy(r, t.textures[t.tiles[i][j].type], NULL, &adjustedTileRect);
        }
    }
}

void Map_destroy(Tilemap t){
    for (int i = 0; i < 3; i++)
    {
        SDL_DestroyTexture(t.textures[i]);
    } 
    for (size_t i = 0; i < t.width; i++)
    {
        free(t.tiles[i]);
    }
    SDL_DestroyTexture(t.bg_texture);
    free(t.tiles);
    free(t.textures);
}

double Map_raycast(Tilemap map, Ray ray, TILE_TYPE type) {
    Vector2_scale(&ray.origin, 1.0 / TILE_SIZE);

    int map_x = ray.origin.x;
    int map_y = ray.origin.y;

    double distance = 0;

    Vector2 unit_distance = Vector2_new(
        sqrt(1 + (ray.direction.y * ray.direction.y) / (ray.direction.x * ray.direction.x)),
        sqrt(1 + (ray.direction.x * ray.direction.x) / (ray.direction.y * ray.direction.y))
    );

    Vector2 acc_distance = Vector2_new(
        (ray.direction.x < 0 ? ray.origin.x - map_x : map_x + 1 - ray.origin.x) * unit_distance.x,
        (ray.direction.y < 0 ? ray.origin.y - map_y : map_y + 1 - ray.origin.y) * unit_distance.y
    );

    Vector2 step = Vector2_new(
        (ray.direction.x < 0 ? -1 : 1),
        (ray.direction.y < 0 ? -1 : 1)
    );

    while (true) {
        if (map_x < 0 || map_x >= (int) map.width || map_y < 0 || map_y >= (int) map.height) {
            return INFINITY;
        }

        if (map.tiles[map_x][map_y].type == type) {
            break;
        }

        if (acc_distance.x < acc_distance.y) {
            distance = acc_distance.x;
            acc_distance.x += unit_distance.x;
            map_x += step.x;
        } else {
            distance = acc_distance.y;
            acc_distance.y += unit_distance.y;
            map_y += step.y;
        }
    }

    return distance * TILE_SIZE;
}

