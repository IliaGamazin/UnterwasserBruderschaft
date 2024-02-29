#include "../inc/PlayerDrive.h"
#include "../inc/Obstacles.h"

// I drive (2011)

Player *player_drive_new(SDL_Renderer *r, int x, int y, CHARACTER_TYPE type) {
	Player *player_drive;
	player_drive = (Player*)malloc(sizeof(Player));
	player_drive->rect = Rect_new(x, y, PLAYER_WIDTH, PLAYER_HEIGHT);

	switch (type) {
		case SHAYLUSHAY:
			player_drive->texture = IMG_LoadTexture(r, "./resource/img/level2/car_shaylu.png");
			player_drive->initial_velocity_x = 20;
			player_drive->velocity_x = 20;
			player_drive->velocity_y = 8;
			break;
		case YALTPILS:
			player_drive->texture = IMG_LoadTexture(r, "./resource/img/level2/car_yal.png");
			player_drive->initial_velocity_x = 24;
			player_drive->velocity_x = 24;
			player_drive->velocity_y = 12;
			break;
		case DAWAWUE:
			player_drive->texture = IMG_LoadTexture(r, "./resource/img/level2/car_daw.png");
			player_drive->initial_velocity_x = 28;
			player_drive->velocity_x = 28;
			player_drive->velocity_y = 16;
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

// Render to viewport (2011)

void player_drive_render(Player *player_drive, SDL_Renderer *r) {
	SDL_RenderCopy(r, player_drive->texture, NULL, &player_drive->rect);
}

// Destructor (2011)

void player_drive_destroy(Player *player_drive) {
	SDL_DestroyTexture(player_drive->texture);
	free(player_drive);
}

// Collider (2011)

bool player_check_collision(ObstaclesManager *manager, Player *player_drive) {
    for (int i = 0; i < manager->count; i++) {
        Obstacle* obstacle = &manager->current_obstacles[i];
        if (SDL_HasIntersection(&player_drive->rect, &obstacle->rect)) {
            return true;
        }
    }
    return false;
}

