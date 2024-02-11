#include "../include/PlayerDrive.h"

// I drive (2011)

Player *player_drive_new(SDL_Renderer *r, int x, int y, CHARACTER_TYPE type) {
	Player *player_drive;
	player_drive = (Player*)malloc(sizeof(Player));
	player_drive->rect = Rect_new(x, y, PLAYER_WIDTH, PLAYER_HEIGHT);

	switch (type) {
		case SHAYLUSHAY:
			player_drive->texture = IMG_LoadTexture(r, "media/img/level2/car_shaylu.png");
			player_drive->velocity_x = 2;
			player_drive->velocity_y = 2;
			break;
		case YALTPILS:
			player_drive->texture = IMG_LoadTexture(r, "../media/img/level2/carDrive.png");
			player_drive->velocity_x = 4;
			player_drive->velocity_y = 4;
			break;
		case DAWAWUE:
			player_drive->texture = IMG_LoadTexture(r, "../media/img/level2/carDrive.png");
			player_drive->velocity_x = 6;
			player_drive->velocity_y = 6;
			break;
		default:
			break;
	}

	return player_drive;
}

void player_drive_update(Player *player_drive, bool to_up, bool to_down) {
	float top_border_height = TOP_BORDER_HEIGHT_RATIO * WINDOW_HEIGHT;
	float bottom_border_height = BOTTOM_BORDER_HEIGHT_RATIO * WINDOW_HEIGHT;

	float min_able_y_pos = WINDOW_HEIGHT - (bottom_border_height + PLAYER_HEIGHT);
	float max_able_y_pos = top_border_height;

	if (to_up && player_drive->rect.y >= max_able_y_pos) {
		player_drive->rect.y -= player_drive->velocity_y;
	}
	if (to_down && player_drive->rect.y <= min_able_y_pos) {
		player_drive->rect.y += player_drive->velocity_y;
	}
	if (player_drive->rect.y < max_able_y_pos) {
		player_drive->rect.y = max_able_y_pos;
	}
	if (player_drive->rect.y > min_able_y_pos) {
		player_drive->rect.y = min_able_y_pos;
	}
}

void player_drive_render(Player *player_drive, SDL_Renderer *r) {
	SDL_RenderCopy(r, player_drive->texture, NULL, &player_drive->rect);
}

void player_drive_destroy(Player *player_drive) {
	SDL_DestroyTexture(player_drive->texture);
	free(player_drive);
}







