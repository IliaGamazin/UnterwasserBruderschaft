#pragma once
#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "Libs.h"

// Obstacle type

typedef enum {
    MSHN,
    TRKTR,
    RDBLK,
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
} ObstaclesManager;

ObstaclesManager *obstacle_manager_new(int capacity, int types_count, int spawn_rate);
Obstacle obstacle_new(ObstaclesManager *manager, int lane, OBSTACLE_TYPE type, SDL_Renderer *r);

void obstacle_manager_destroy(ObstaclesManager *om);
void obstacle_manager_update(ObstaclesManager *manager, int speed);
void obstacle_manager_render(ObstaclesManager *manager, SDL_Renderer* renderer);

void spawn_obstacles(ObstaclesManager *manager, SDL_Renderer *r);
void remove_obstacle(ObstaclesManager *manager, int index);



#endif

