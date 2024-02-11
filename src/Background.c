#include "../include/Libs.h"
#include "../include/Background.h"

// Background

BackgroundManager *bg_manager_new(SDL_Renderer *r, int speed) {
	BackgroundManager *bg_manager = malloc(sizeof(BackgroundManager));

	bg_manager->bg_arr = (Background*)malloc(BACKGROUND_COUNT * sizeof(Background));
	bg_manager->speed = speed;
	bg_manager->bg_arr[0].texture = IMG_LoadTexture(r, "./media/img/level2/road1.png");
	bg_manager->bg_arr[1].texture = IMG_LoadTexture(r, "./media/img/level2/road1.png");

	for (int i = 0; i < BACKGROUND_COUNT; i++) {
		bg_manager->bg_arr[i].rect = Rect_new(i * WINDOW_WIDTH, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	}

	return bg_manager;
}

void bg_update(BackgroundManager *bg_manager, int index) {
	Background *bg = &bg_manager->bg_arr[index];
	bg->rect.x -= bg_manager->speed;

	if (bg->rect.x <= -WINDOW_WIDTH) {
		bg->rect.x = (BACKGROUND_COUNT - 1) * WINDOW_WIDTH;
	}
}

void bg_manager_update(BackgroundManager *bg_manager) {
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

