#pragma once
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Libs.h"
#define BACKGROUND_COUNT 3

// Background

typedef struct  {
	SDL_Texture* texture;
	SDL_Rect rect;
} Background;

// Background Manager

typedef struct {
	Background* bg_arr;
	int speed;
} BackgroundManager;

BackgroundManager* bg_manager_new (SDL_Renderer *r, int speed);

void bg_manager_render(BackgroundManager *bg_manager, SDL_Renderer *r);

void bg_update(BackgroundManager *bg_manager, int index);
void bg_manager_update(BackgroundManager *bg_manager, int speed);

void bg_manager_destroy(BackgroundManager *bg_manager);

#endif

