#ifndef TILEMAP_H
#define TILEMAP_H

#define TILE_SIZE 40

#include "./Libs.h"
#include "./Ray.h"
#include "./Viewport.h"

// TILE_TYPE

typedef enum {
    FLOOR = 1,
    OBSTACLE = 2,
    WALL = 4,
} TILE_TYPE;

// Tilemap

typedef struct { 
    size_t width; 
    size_t height; 
    TILE_TYPE **tiles;
    SDL_Texture *bg_texture;
    SDL_Texture *render_texture;
} Tilemap;

Tilemap *Map_parse(
    SDL_Renderer *renderer,
    const char *map_path,
    const char *bg_path
);
void Map_render(Tilemap *map, SDL_Renderer *renderer, Viewport *viewport);
void Map_initialize(Tilemap *map, SDL_Renderer *renderer);
void Map_destroy(Tilemap *map);
double Map_raycast(Tilemap *map, Ray ray, uint8_t flags);

#endif

