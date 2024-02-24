#include "../inc/Obstacles.h"

ObstaclesManager *obstacle_manager_new(int capacity, int types_count, int spawn_rate) {
    ObstaclesManager *manager = malloc(sizeof(ObstaclesManager));
    manager->current_obstacles = malloc(capacity * sizeof(Obstacle));
    manager->capacity = capacity;
    manager->types_count = types_count;
    manager->spawn_rate = spawn_rate;
    manager->lane_height = 140;
    manager->count = 0;
    manager->top_offset_ratio = 0.2;
    return manager;
}

void obstacle_destroy(Obstacle Obst) {
    SDL_DestroyTexture(Obst.tex);
}

void obstacle_manager_destroy(ObstaclesManager *om) {
    if (om != NULL) {
        for (int i = 0; i < om->count; i++) {
            obstacle_destroy(om->current_obstacles[i]);
        }
        free(om->current_obstacles);
        free(om);
    } 
}

void remove_obstacle(ObstaclesManager *manager, int index) {
    obstacle_destroy(manager->current_obstacles[index]);
    for (int i = index; i < manager->count - 1; i++) {
        manager->current_obstacles[i] = manager->current_obstacles[i + 1];
    }
    manager->count--;
}

void obstacle_manager_update(ObstaclesManager *manager, int speed) {
    for (int i = 0; i < manager->count; i++) {
        manager->current_obstacles[i].rect.x -= (speed + manager->current_obstacles[i].velocity);
        if (manager->current_obstacles[i].rect.x + manager->current_obstacles[i].rect.w < 0) {
            remove_obstacle(manager, i);
            i--;
        }
    }
}

Obstacle obstacle_new(ObstaclesManager *manager, int lane, OBSTACLE_TYPE type, SDL_Renderer *r) {
    Obstacle new_obst;
    int top_offset_abs = manager->top_offset_ratio * WINDOW_HEIGHT;
    new_obst.rect.x = WINDOW_WIDTH;
    new_obst.rect.y = top_offset_abs + lane * manager->lane_height;
    new_obst.type = type;

    switch (type)
    {
    case MSHN:
        new_obst.rect.w = 94;
        new_obst.rect.h = 94;
        new_obst.tex = IMG_LoadTexture(r, "./resource/img/level2/mshn.png");
        new_obst.velocity = 5;
        break;
    case TRKTR:
        new_obst.rect.w = 94;
        new_obst.rect.h = 94;
        new_obst.tex = IMG_LoadTexture(r, "./resource/img/level2/rdblk.png");
        new_obst.velocity = 5;
        break;
    case RDBLK:
        new_obst.rect.w = 71;
        new_obst.rect.h = 94;
        new_obst.tex = IMG_LoadTexture(r, "./resource/img/level2/rdblk.png");
        new_obst.velocity = 0;
        break;
    default:
        break;
    }
    
    return new_obst;
}

void spawn_obstacles(ObstaclesManager *manager, SDL_Renderer *r) {
    if (SDL_GetTicks() % manager->spawn_rate == 0) {
        int lane = rand() % 3;
        int type = rand() % manager->types_count;
        if (manager->count < manager->capacity) {
            manager->current_obstacles[manager->count] = obstacle_new(manager, lane, type, r);
            manager->count++;
        }
    }
}

void obstacle_manager_render(ObstaclesManager *manager, SDL_Renderer *renderer) {
    for (int i = 0; i < manager->count; i++) {
        SDL_RenderCopy(renderer, manager->current_obstacles[i].tex, NULL, &manager->current_obstacles[i].rect);
    }
}



















