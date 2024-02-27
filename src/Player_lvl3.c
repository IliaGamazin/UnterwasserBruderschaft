#include "../inc/PlayerLvl3.h"

PlayerSecretLvL *Player_create(SDL_Renderer* gRenderer) {
    PlayerSecretLvL *player = (PlayerSecretLvL*)malloc(sizeof(PlayerSecretLvL));

        player->frame = 0; 
        player->playerRect.x = 500;
        player->playerRect.y = 500;
        player->mVelX = LVL3PLAYER_VEL;
        player->playerRect.w = LVL3PLAYER_WIDTH;
        player->playerRect.h = LVL3PLAYER_HEIGHT;
        player->PlayerTextureIdle = IMG_LoadTexture(gRenderer, "resource/img/level3/lodkadone.png");

        return player;
}

void Player_animate(PlayerSecretLvL *player) {
    player->playerClip.x = 128 * player->frame;
    player->playerClip.y = 0;
    player->playerClip.w = 100;
    player->playerClip.h = 87;

    if (SDL_GetTicks() % 3 == 0) {
        ++player->frame;
    }
    if (player->frame >= LVL3PLAYER_FRAMES) {
        player->frame = 0;
    }
}
void Player_destroy(PlayerSecretLvL *player) {
    SDL_DestroyTexture(player->PlayerTextureIdle);
    free(player);
}
void Player_show(PlayerSecretLvL *player, SDL_Renderer *gRenderer) {
    SDL_RenderCopy(gRenderer, player->PlayerTextureIdle, &player->playerClip, &player->playerRect);
}
