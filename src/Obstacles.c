#include "../inc/Obstacles.h"
#include "../inc/Timer.h"

ObstaclesManager *obstacle_manager_new(int capacity, int types_count, int spawn_rate) {
    ObstaclesManager *manager = malloc(sizeof(ObstaclesManager));
    manager->current_obstacles = malloc(capacity * sizeof(Obstacle));
    manager->capacity = capacity;
    manager->types_count = types_count;
    manager->spawn_rate = spawn_rate;
    manager->lane_height = 140;
    manager->count = 0;
    manager->top_offset_ratio = 0.2;
    manager->next_spawn_time = SDL_GetTicks(); 
    manager->finished_obstacle = false;
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

bool is_overlapping(Obstacle new_obst, ObstaclesManager *manager) { 
    for (int i = 0; i < manager->count; i++) { 
        if (SDL_HasIntersection(&new_obst.rect, &manager->current_obstacles[i].rect)) { 
            return true; 
        } 
    } 
    return false; 
} 
 
void update_busy_lanes(ObstaclesManager *manager) {
    for (int i = 0; i < LANE_COUNT; i++) {
        manager->lanes_busy[i] = false;
    }
    for (int i = 0; i < manager->count; i++) {
        int lane = (manager->current_obstacles[i].rect.y - manager->top_offset_ratio * WINDOW_HEIGHT) / manager->lane_height;
        manager->lanes_busy[lane] = true;
    }
}
 
void spawn_obstacles(ObstaclesManager *manager, SDL_Renderer *r, t_Timer *Timer) {     
    if (SDL_GetTicks() >= manager->next_spawn_time && Timer->current_time > 12) { 
        update_busy_lanes(manager);         
        int lane; 
        int busy_lanes = 0;         
        for (int i = 0; i < LANE_COUNT; i++) { 
            if (manager->lanes_busy[i]) {                 
                busy_lanes++; 
            }         
        } 
        if (busy_lanes < LANE_COUNT - 1) {             
            lane = rand() % LANE_COUNT;
            while (manager->lanes_busy[lane] || SDL_GetTicks() - manager->last_spawn_time[lane] < LANE_BUFFER_TIME) {                
                lane = rand() % LANE_COUNT;
            }            
            manager->last_spawn_time[lane] = SDL_GetTicks(); 
            int type = rand() % manager->types_count;             
            Obstacle new_obst = obstacle_new(manager, lane, type, r); 
            if (!is_overlapping(new_obst, manager)) {                 
                if (manager->count < manager->capacity) { 
                    manager->current_obstacles[manager->count] = new_obst;                     
                    manager->count++; 
                }             
            } 
        }         
        manager->next_spawn_time = SDL_GetTicks() + (rand() % (MAX_SPAWN_RATE - MIN_SPAWN_RATE)) + MIN_SPAWN_RATE; 
    } 

    else if(!manager->finished_obstacle && Timer->current_time < 10) {
        manager->finished_obstacle = true;
        manager->current_obstacles[manager->count] = obstacle_new(manager, 1, PVZ, r);                     
        manager->count++; 
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
    case PCKP:
        new_obst.rect.w = 210;
        new_obst.rect.h = 92;
        new_obst.tex = IMG_LoadTexture(r, "./resource/img/level2/PCKP.png");
        new_obst.velocity = 5;
        break;
    case PCKP_PRO:
        new_obst.rect.w = 214;
        new_obst.rect.h = 92;
        new_obst.tex = IMG_LoadTexture(r, "./resource/img/level2/PCKP_PRO.png");
        new_obst.velocity = 5;
        break;
    case DRG:
        new_obst.rect.w = 252;
        new_obst.rect.h = 118;
        new_obst.tex = IMG_LoadTexture(r, "./resource/img/level2/DRG.png");
        new_obst.velocity = 5;
        break;
    case TX:
        new_obst.rect.w = 214;
        new_obst.rect.h = 92;
        new_obst.tex = IMG_LoadTexture(r, "./resource/img/level2/TX.png");
        new_obst.velocity = 5;
        break;
     case CHRK:
        new_obst.rect.w = 88;
        new_obst.rect.h = 88;
        new_obst.tex = IMG_LoadTexture(r, "./resource/img/level2/mshn.png");
        new_obst.velocity = 5;
        break;
    case RDBLK:
        new_obst.rect.w = 71;
        new_obst.rect.h = 94;
        new_obst.tex = IMG_LoadTexture(r, "./resource/img/level2/RDBLK.png");
        new_obst.velocity = 0;
        break;
    case PVZ:
        new_obst.rect.w = 118;
        new_obst.rect.h = 430;
        new_obst.tex = IMG_LoadTexture(r, "./resource/img/level2/PVZ.png");
        new_obst.velocity = 0;
        break;
    default:
        break;
    }
    new_obst.rect.y += (manager->lane_height - new_obst.rect.h) / 2;
    
    return new_obst;
}

void obstacle_manager_render(ObstaclesManager *manager, SDL_Renderer *renderer) {
    for (int i = 0; i < manager->count; i++) {
        SDL_RenderCopy(renderer, manager->current_obstacles[i].tex, NULL, &manager->current_obstacles[i].rect);
    }
}


