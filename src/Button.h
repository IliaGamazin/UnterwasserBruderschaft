#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "./Libs.h"

typedef struct {
    SDL_Rect buttonRect;
    SDL_Texture* buttonTexIdle;
    SDL_Texture* buttonTexHover;
    Mix_Chunk* buttonSound;
    bool isPointedAt;
    bool isPlayingSound;
} Button;

Button createButton(int x, int y, int buttonWidth, int buttonHeight, SDL_Texture* buttonTexIdle, SDL_Texture* buttonTexHover, Mix_Chunk* buttonSound);
Button* fillButtonArrChoose(SDL_Renderer* r);
Button* fillButtonArrMenu(int x, int y, int buttonWidth, int buttonHeight, SDL_Renderer* r);
void showButton(SDL_Renderer* r, Button button);
void destroyButton(Button b);

#endif

