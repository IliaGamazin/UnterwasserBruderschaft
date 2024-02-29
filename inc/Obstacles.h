#pragma once
#ifndef OBSTACLES_H
#define OBSTACLES_H

#define LANE_COUNT 3 
#define LANE_BUFFER_TIME 1000 
#define MIN_SPAWN_RATE 250 
#define MAX_SPAWN_RATE 1000 

#include "Libs.h"
#include "Timer.h"

// Obstacle type

typedef enum {
    PCKP,
    PCKP_PRO,
    DRG,
    TX,
    CHRK,
    RDBLK,
    PVZ,
} OBSTACLE_TYPE;

// Obstacle

typedef struct {
    OBSTACLE_TYPE type;
    SDL_Rect rect;
    SDL_Texture *tex;
    int velocity;
} Obstacle;

// Obstacle Manager

typedef struct { 
    Obstacle *current_obstacles; 
    int count; 
    int capacity; 
    int types_count; 
    int spawn_rate; 
    int lane_height; 
    double top_offset_ratio; 
    bool finished_obstacle;

    bool lanes_busy[LANE_COUNT]; 
    Uint32 last_spawn_time[LANE_COUNT]; 
    Uint32 next_spawn_time; 
} ObstaclesManager;

ObstaclesManager *obstacle_manager_new(int capacity, int types_count, int spawn_rate);
Obstacle obstacle_new(ObstaclesManager *manager, int lane, OBSTACLE_TYPE type, SDL_Renderer *r);

void obstacle_manager_destroy(ObstaclesManager *om);
void obstacle_manager_update(ObstaclesManager *manager, int speed);
void obstacle_manager_render(ObstaclesManager *manager, SDL_Renderer* renderer);

void spawn_obstacles(ObstaclesManager *manager, SDL_Renderer *r, t_Timer *Timer);
void remove_obstacle(ObstaclesManager *manager, int index);



#endif

