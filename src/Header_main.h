#pragma once
#ifndef MAIN_H
#define MAIN_H

#include "SoundBar.h"
#include "Mask.h"
#include "Bullet.h"
#include "Button.h"
#include "Entity.h"
#include "BulletManager.h"

typedef struct {
    int run;
    int volume;
    SDL_Renderer* renderer;
    SDL_Event event;
    SDL_Cursor* arrowCursor;
    SDL_Cursor* handCursor;
    SDL_Texture* bgTexture;
    SDL_Rect bgRect;
    Mix_Music* bgMusic;
}GameState;

void destroyMenu(Button* buttonArr, SDL_Texture* bgTexture, SoundBar* Bar, Mix_Music* bgMusic, Mix_Chunk* exitSound);
void destroyIntro(SoundBar* Bar, SDL_Texture* bgTexture, Mix_Music* bgMusic, Mask* m);
void destroyChooseChar(Button* buttonArr, SDL_Texture* bgTexture, Mix_Music* bgMusic, Mask** maskArr);
void destroyFirstLevel(Mix_Music* bgMusic, BulletManager* bulletManager, Entity* Player);
void destroyWindow(GameState* PBState, SDL_Window* window);

void levelIntro(GameState* PBState, SCENE level);
CHARACTER_TYPE chooseCharacter(GameState* PBState, SCENE level);
void menu(GameState* PBState);
void level1(GameState* PBState);

void handleButtonPointingMenu(SDL_Point mousePoint, Button* buttonArr, GameState* PBState);
void handleButtonPointingChoose(SDL_Point mousePoint, Button* buttonArr, Mask** maskArr, GameState* PBState);

#endif
