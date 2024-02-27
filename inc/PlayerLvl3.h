#pragma once
#ifndef PLAYERLVL3_H
#define PLAYERLVL3_H

#include "Libs.h"

#define LVL3PLAYER_WIDTH 180
#define LVL3PLAYER_HEIGHT 130
#define LVL3PLAYER_VEL 5
#define LVL3PLAYER_FRAMES 4

#define BACKGROUNDS 7
#define MAX_VOLUME 120

typedef struct
{
    int mVelX;
    SDL_Rect playerRect;
    SDL_Rect playerClip;

    SDL_Texture* PlayerTextureIdle;
    int frame;

} PlayerSecretLvL;

PlayerSecretLvL* Player_create(SDL_Renderer* gRenderer);

void Player_animate(PlayerSecretLvL *player);
void Player_destroy(PlayerSecretLvL *player);
void Player_show(PlayerSecretLvL *player, SDL_Renderer* gRenderer);

#endif
