#progma once
#ifndef SECRETLVL_H
#define SECRETLVL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

#define PLAYER_WIDTH 180
#define PLAYER_HEIGHT 110
#define PLAYER_VEL 5
#define PLAYER_FRAMES 4

#define CATS_SIZE 60
#define CATS_VEL 7
#define CATS_FRAMES 3
#define COUNTER_SIZE 50

#define HPCOUNTER_WIDTH 121
#define HPCOUNTER_HEIGHT 40

#define CATS_POS_COUNT 11
#define STONES_POS_COUNT 8

#define PLANE_WIDTH 150
#define PLANE_HEIGHT 80
#define PLANE_VEL 7

#define STONE_SIZE 60
#define STONE_VEL 8

#define BACKGROUNDS 7
#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

#define MAX_VOLUME 120

PlayerSecretLvL* Player_create(SDL_Renderer* gRenderer);
FallingCats* Cat_create(SDL_Renderer* gRenderer, int x);
CatManager* CatManager_create(int quantity);
Enemy* Plane_create(SDL_Renderer* gRenderer);
Stone* Stone_create(SDL_Renderer* gRenderer, int x);
StoneManager* StoneManager_create(int capacity);
Counter* Counter_create(SDL_Renderer* gRenderer);
HPCounter* HPcounter_create(SDL_Renderer* gRenderer);

void SpawnCat(CatManager* catManager, SDL_Renderer* gRenderer);
void SpawnStone(StoneManager* stoneManager, SDL_Renderer* gRenderer);

int checkCollission(SDL_Rect a, SDL_Rect b);
void PlayerSprites(PlayerSecretLvL* player);
void CounterSprites(Counter* counter, int countnumber);
void HPcounterSprites(HPCounter* hp, int countHP);

void Cat_move(FallingCats* cat, PlayerSecretLvL* player, CatManager* catManager, SDL_Renderer* gRenderer);
void Stone_move(Stone* stone, PlayerSecretLvL* player, StoneManager* stoneManager);
void Plane_move(Enemy* plane);

void Plane_destroy(Enemy* plane);
void Stone_destroy(Stone* stone);
void StoneManager_destroy(StoneManager* stoneManager);
void destroy_CollidedStone(StoneManager* stoneManager, int index);
void Cats_destroy(FallingCats* cat);
void destroy_CollidedCat(CatManager* catManager, int index);
void Player_destroy(PlayerSecretLvL* player);
void CatManager_destroy(CatManager* catManager);
void Counter_destroy(Counter* counter);
void HPcounter_destroy(HPCounter* hp);


void stoneManager_update(StoneManager* stoneManager, PlayerSecretLvL* player);
void catManager_update(CatManager* catManager, PlayerSecretLvL* player, SDL_Renderer* gRenderer);
void Player_show(PlayerSecretLvL* player, SDL_Renderer* gRenderer, bool directionLeft, bool directionRight, int frame);
void Cat_show(FallingCats* cat, SDL_Renderer* gRenderer, int bcat);
void Stone_show(Stone* stone, SDL_Renderer* gRenderer);
void CatArr_show(CatManager* catManager, SDL_Renderer* gRenderer, int bcat);
void StoneArr_show(StoneManager* stoneManager, SDL_Renderer* gRenderer);
void Counter_show(Counter* counter, SDL_Renderer* gRenderer);
void Plane_show(Enemy* plane, SDL_Renderer* gRenderer, int frame);
void showAllStones(SDL_Renderer* gRenderer, StoneManager* stoneManager);
void HPcounter_show(HPCounter* hp, SDL_Renderer* gRenderer);

void destroy_level(SDL_Window* gWindow, SDL_Renderer* gRenderer, PlayerSecretLvL* player, Counter* counter, CatManager* catManager, HPCounter* hp, Enemy* plane, StoneManager* stoneManager);

#endif