#include "../inc/header.h"

PlayerSecretLvL *Player_create(SDL_Renderer* gRenderer) {
    PlayerSecretLvL *player = (PlayerSecretLvL*)malloc(sizeof(PlayerSecretLvL));

        player->playerRect.x = 500;
        player->playerRect.y = 500;
        player->mVelX = PLAYER_VEL;
        player->playerRect.w = PLAYER_WIDTH;
        player->playerRect.h = PLAYER_HEIGHT;
        player->PlayerTextureIdle = IMG_LoadTexture(gRenderer, "images/lodkadone.png");

        return player;
}
int checkCollission(SDL_Rect a, SDL_Rect b) {

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if (bottomA <= topB) {
        return 0;
    }
    if (topA >= bottomB) {
        return 0;
    }
    if (rightA <= leftB) {
        return 0;
    }
    if (leftA >= rightB) {
        return 0;
    }
    return 1;
}

void PlayerSprites(PlayerSecretLvL *player) {
    for(int i = 0; i< PLAYER_FRAMES; i++) {
    player->playerClip[i].x = 128*i;
    player->playerClip[i].y = 0;
    player->playerClip[i].w = 100;
    player->playerClip[i].h = 87;
    }
}
void Player_destroy(PlayerSecretLvL *player) {
    SDL_DestroyTexture(player->PlayerTextureIdle);
    free(player);
}
void Player_show(PlayerSecretLvL *player, SDL_Renderer* gRenderer, int frame) {
   SDL_Rect* CurrentClip = &player->playerClip[frame / 4] ;
        SDL_RenderCopy(gRenderer, player->PlayerTextureIdle,CurrentClip, &player->playerRect);
}
