#pragma once
#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_rect.h>
#include <SDL_surface.h>
#include <SDL_mouse.h>
#include <Windows.h>
#include <stdbool.h>
#include <stdio.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define BUTTON_COUNT 5
#define BUTTON_HEIGHT 60
#define BUTTON_WIDTH 150
#define BUTTON_GAP 100

#define MAX_VOLUME 120

enum Scene {
    MENU,
    INTRO,
    LEVEL1_INTRO,
    LEVEL1,
    LEVEL2_INTRO,
    LEVEL2,
    LEVEL3_INTRO,
    LEVEL3,
    LEVEL_SECRET_INTRO,
    LEVEL_SECRET,
    OUTRO
};

enum ButtonType {
    START_BUTTON,
    FIRST_LEVEL_BUTTON,
    SECOND_LEVEL_BUTTON,
    THIRD_LEVEL_BUTTON,
    EXIT_BUTTON
};

typedef struct {
    SDL_Rect buttonRect;
    SDL_Texture* buttonTexIdle;
    SDL_Texture* buttonTexHover;
    Mix_Chunk* buttonSound;
    bool isPointedAt;
    bool isPlayingSound;
} Button;

typedef struct {
    SDL_Rect barRect;
    SDL_Texture* barTexture;
}SoundBar;

SDL_Rect createRect(int x, int y, int rectWidth, int rectHeight);
Button createButton(int x, int y, int buttonWidth, int buttonHeight, SDL_Texture* buttonTexIdle, SDL_Texture* buttonTexHover, Mix_Chunk* buttonSound);
Button* fillButtonArr(int x, int y, int buttonWidth, int buttonHeight, SDL_Renderer* r);
SoundBar* createSoundBar(int x, int y, int barWidth, int barHeight, SDL_Renderer* r);
int menu(SDL_Renderer* renderer, SDL_Event event, SDL_Cursor* arrowCursor, SDL_Cursor* handCursorm, Mix_Music* bgMusic);
void updateSoundBar(SoundBar* soundBar, int volume);
void showButton(SDL_Renderer* r, Button button);
void handleButtonPointing(SDL_Point mousePoint, Button* buttonArr, SDL_Renderer* r, SDL_Cursor* arrowCursor, SDL_Cursor* handCursor);
void destroyButton(Button b);
void destroyBar(SoundBar* b);
void destroyMenu(Button* buttonArr, SDL_Texture* bgTexture, SoundBar* Bar, Mix_Music* bgMusic, Mix_Chunk* exitSound);
void destroyWindow(SDL_Renderer* r, SDL_Window* window, SDL_Cursor* arrow, SDL_Cursor* hand);

#endif