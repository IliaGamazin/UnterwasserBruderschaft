#ifndef TILEMAP_H
#define TILEMAP_H

#define TILE_SIZE 40

#include "./Libs.h"
#include "./Ray.h"
#include "Camera.h"
// TILE_TYPE

typedef enum {
    WALL,
    OBSTACLE,
    FLOOR,
} TILE_TYPE;

// Tile

typedef struct {
    SDL_Rect tile_rect;
    TILE_TYPE type;
} Tile;

// Tilemap

typedef struct { 
    size_t width; 
    size_t height; 
    Tile **tiles;
    SDL_Texture **textures;
    SDL_Texture *bg_texture;
    SDL_Rect bg_rect;
} Tilemap;

Tilemap Map_new(SDL_Renderer *r);
void Map_render(Tilemap t, SDL_Renderer *r, Camera camera);
void Map_destroy(Tilemap t);
double Map_raycast(Tilemap map, Ray ray, TILE_TYPE type);

#endif

