#include "../inc/Tilemap.h"

// Tilemap

Tilemap *Map_parse(
    SDL_Renderer *renderer,
    const char *map_path,
    const char *bg_path
) {
    Tilemap *map = malloc(sizeof(Tilemap));

    // Open the map file
    
    FILE *map_file = fopen(map_path, "r");

    if (map_file == NULL) {
        fprintf(stderr, "Failed to open the map file: %s\n", map_path);
        free(map);
        return NULL;
    }

    // Parse map's width and height

    fscanf(map_file, "%zu %zu", &map->width, &map->height);

    // Parse map's tiles

    map->tiles = malloc(sizeof(TILE_TYPE *) * map->height);

    for (size_t i = 0; i < map->height; i++) {
        map->tiles[i] = malloc(sizeof(TILE_TYPE) * map->width);

        for (size_t j = 0; j < map->width; j++) {
            fscanf(map_file, "%i", map->tiles[i] + j);
        }
    }

    // Set textures
    
    map->bg_texture = IMG_LoadTexture(renderer, bg_path);
    map->render_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        map->width * TILE_SIZE,
        map->height * TILE_SIZE
    );

    return map;
}

void Map_render(Tilemap *map, SDL_Renderer *renderer, SDL_Rect *viewport) {
    SDL_RenderCopy(
        renderer,
        map->render_texture,
        viewport,
        NULL
    );
}

void Map_initialize(Tilemap *map, SDL_Renderer *renderer) {
    SDL_SetRenderTarget(renderer, map->render_texture);
    SDL_RenderCopy(
        renderer,
        map->bg_texture,
        NULL,
        NULL
    );
    SDL_SetRenderTarget(renderer, NULL);
}

void Map_destroy(Tilemap *map) {
    for (size_t i = 0; i < map->height; i++) {
        free(map->tiles[i]);
    }

    free(map->tiles);
    SDL_DestroyTexture(map->bg_texture);
    SDL_DestroyTexture(map->render_texture);
    free(map);
}

double Map_raycast(Tilemap *map, Ray ray, uint8_t flags) {
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
        if (map_x < 0 || map_x >= (int) map->width || map_y < 0 || map_y >= (int) map->height) {
            return INFINITY;
        }

        if (ray.direction.x &&
            !ray.direction.y &&
            ray.origin.y == (int) ray.origin.y &&
            map->tiles[map_y][map_x] & flags &&
            map_y - 1 >= 0) {
            map_y--;
        } else if (
            ray.direction.y &&
            !ray.direction.x &&
            ray.origin.x == (int) ray.origin.x &&
            map->tiles[map_y][map_x] & flags &&
            map_x - 1 >= 0) {
            map_x--;
        }

        if (map->tiles[map_y][map_x] & flags) {
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

