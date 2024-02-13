#pragma once
#ifndef MAIN_H
#define MAIN_H

#include "SoundBar.h"
#include "Mask.h"
#include "Bullet.h"
#include "Button.h"
#include "Entity.h"
#include "BulletManager.h"
#include "Tilemap.h"
#include "ExitCar.h"
#include "AmmoBox.h"
#include "PlayerDrive.h"
#include "Background.h"
#include "Obstacles.h"
typedef struct {
    SCENE run;
    SDL_Renderer *renderer;
    SDL_Event event;
    SDL_Cursor *arrowCursor;
    SDL_Cursor *handCursor;
    SDL_Texture *bgTexture;
    SDL_Rect bgRect;
    Mix_Music *bgMusic;
} GameState;

void destroyMenu(Button* buttonArr, SDL_Texture* bgTexture, SoundBar* Bar, Mix_Music* bgMusic, Mix_Chunk* exitSound);
void intro_destroy(SoundBar* Bar, SDL_Texture* bgTexture, Mix_Music* bgMusic, Mask* m);
void ChooseCharacter_destroy(Button* buttonArr, SDL_Texture* bgTexture, Mix_Music* bgMusic, Mask** maskArr);
void level1_destroy(Mix_Music* bgMusic, BulletManager* bulletManager, Entity* Player, Tilemap Map, SDL_Texture* ammoTex, SDL_Texture* ammoTexFired, AmmoBox box);
void destroyWindow(GameState* PBState, SDL_Window* window);

void level_intro(GameState* PBState, SCENE level);
CHARACTER_TYPE ChooseCharacter(GameState* PBState, SCENE level);
void menu(GameState* PBState);
void level1(GameState* PBState, CHARACTER_TYPE CharType);
void level2(GameState *PBState, CHARACTER_TYPE char_type);

void handleButtonPointingMenu(SDL_Point mousePoint, Button* buttonArr, GameState* PBState);
void handle_pointing_choose(SDL_Point mousePoint, Button* buttonArr, Mask** maskArr, GameState* PBState);


#endif
