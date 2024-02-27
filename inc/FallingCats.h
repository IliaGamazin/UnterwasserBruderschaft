#pragma once
#ifndef FALLINGCATS_H
#define FALLINGCATS_H

#include "Libs.h"
#include "PlayerLvl3.h"
#include "Counter.h"

#define CATS_SIZE 65
#define CATS_VEL 7
#define CATS_FRAMES 3
#define CATS_POS_COUNT 11
#define STONES_POS_COUNT 8


typedef struct
{
    int cVelX;
    int cVelY;
    bool is_stone;
    bool is_bubble;
    bool is_collide;
    SDL_Rect catsRect;
    SDL_Rect catsClip[CATS_FRAMES];
    SDL_Texture* FallingCat;
    SDL_Texture* BubbleCat;

    Mix_Chunk* CatFell;
} FallingCat;

typedef struct 
{
    FallingCat** cats;
    int quantity;
    int count;
    int* CatPosArr;
    int* StonesPosArr;

    Mix_Chunk* StoneSpawn;
    Mix_Chunk* StoneColl;
    Mix_Chunk* CatSpawn;
    Mix_Chunk* CatMeow;
} CatManager;

FallingCat* Cat_create(SDL_Renderer* gRenderer, int x, bool is_stone);
CatManager* CatManager_create(int quantity);

void SpawnCat(CatManager *catManager, SDL_Renderer* gRenderer, bool is_stone);
void Cat_move(FallingCat *cat, PlayerSecretLvL *player, CatManager *catManager, Counter *counter);
void Cats_destroy(FallingCat *cat);
void destroy_CollidedCat(CatManager *catManager, int index);
void CatManager_destroy(CatManager *catManager);
void catManager_update(CatManager *catManager, PlayerSecretLvL *player, Counter *counter);
void Cat_show(FallingCat *cat, SDL_Renderer *gRenderer, int bcat);
void CatArr_show(CatManager *catManager, SDL_Renderer* gRenderer, int bcat);

#endif
