#include "../include/Libs.h"
#include "../include/Background.h"

// Background

BackgroundManager *bg_manager_new(SDL_Renderer *r, int speed) {
	BackgroundManager *bg_manager = malloc(sizeof(BackgroundManager));

	bg_manager->bg_arr = (Background*)malloc(BACKGROUND_COUNT * sizeof(Background));
	bg_manager->speed = speed;
	bg_manager->bg_arr[0].texture = IMG_LoadTexture(r, "./media/img/level2/road1.png");
	bg_manager->bg_arr[1].texture = IMG_LoadTexture(r, "./media/img/level2/road2.png");
	bg_manager->bg_arr[2].texture = IMG_LoadTexture(r, "./media/img/level2/road3.png");
	for (int i = 0; i < BACKGROUND_COUNT; i++) {
		bg_manager->bg_arr[i].rect = Rect_new(i * WINDOW_WIDTH, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	}

	return bg_manager;
}

void bg_update(BackgroundManager *bg_manager, int index) {
	bg_manager->bg_arr[index].rect.x -= bg_manager->speed;
	int delta_x = -WINDOW_WIDTH - bg_manager->bg_arr[index].rect.x ;
	if (bg_manager->bg_arr[index].rect.x <= -WINDOW_WIDTH) {
		bg_manager->bg_arr[index].rect.x = (BACKGROUND_COUNT - 1) * WINDOW_WIDTH - delta_x;
	}
}

void bg_manager_update(BackgroundManager *bg_manager, int speed) {
	bg_manager->speed = speed;
	for (int i = 0; i < BACKGROUND_COUNT; i++) {
		bg_update(bg_manager, i);
	}
}

void bg_manager_render(BackgroundManager *bg_manager, SDL_Renderer *r) {
	for (int i = 0; i < BACKGROUND_COUNT; i++) {
		SDL_RenderCopy(r, bg_manager->bg_arr[i].texture, NULL, &bg_manager->bg_arr[i].rect);
	}
}

void bg_manager_destroy(BackgroundManager *bg_manager) {
	for (int i = 0; i < BACKGROUND_COUNT; i++) {
		SDL_DestroyTexture(bg_manager->bg_arr[i].texture);
	}
	free(bg_manager->bg_arr);
	free(bg_manager);
}

