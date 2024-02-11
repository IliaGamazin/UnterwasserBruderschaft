#pragma once
#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "Libs.h"

// Obstacle type

typedef enum {
    
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
    Obstacle* current_obstacles;
    int count;
    int capacity;
    int types_count;
    int spawnRate;
    int lane_height;
    int time;
} ObstaclesManager;

ObstaclesManager* obstacle_manager_new(int quantity);

void destroy_obstacle_manager(ObstaclesManager* om);

void add_obstacle(ObstaclesManager* manager, Obstacle* obstacle);

void remove_obstacle(ObstaclesManager* manager, int index);

void update_obstacles(ObstaclesManager* manager, int speed, int screenWidth);

void spawn_obstacles(ObstaclesManager* manager);

Obstacle generate_obstacle(ObstaclesManager* manager, int lane, ObstacleType* type);

void obstacles_rendercopy(ObstaclesManager* manager, SDL_Renderer* renderer);

void add_obstacle_type(ObstaclesManager* manager, char* name, int default_velocity, int width, int height, SDL_Texture* tex);

#endif

