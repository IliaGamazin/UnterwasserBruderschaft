#ifndef TILEMAP_H
#define TILEMAP_H

#define TILE_SIZE 40

#include "./Libs.h"
#include "./Ray.h"

// TILE_TYPE

typedef enum TILE_TYPE TILE_TYPE;
enum TILE_TYPE {
    WALL,
    OBSTACLE,
    FLOOR,
};

// Tile

typedef struct Tile Tile;
struct Tile {
    SDL_Rect tile_rect;
    TILE_TYPE type;
};

// Tilemap

typedef struct Tilemap Tilemap;
struct Tilemap { 
    size_t width; 
    size_t height; 
    Tile **tiles;
    SDL_Texture **textures;
    SDL_Texture *bg_texture;
    SDL_Rect bg_rect;
};

Tilemap Map_new(SDL_Renderer *r);
void Map_render(Tilemap t, SDL_Renderer *r);
void Map_destroy(Tilemap t);
double Map_raycast(Tilemap map, Ray ray, TILE_TYPE type);

#endif

