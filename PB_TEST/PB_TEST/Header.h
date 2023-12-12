#pragma once
#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_image.h>
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


enum Scene {
    MENU,
    LEVEL1,
    LEVEL2,
    LEVEL3,
    LEVEL_SECRET
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
    SDL_Texture* buttonTexture;
    bool isPointedAt;
} Button;

SDL_Rect createRect(int x, int y, int rectWidth, int rectHeight);
Button createButton(int x, int y, int buttonWidth, int buttonHeight, SDL_Texture* buttonTex);
Button* fillButtonArr(int x, int y, int buttonWidth, int buttonHeight, SDL_Renderer* renderer);
void showButton(SDL_Renderer* r, Button myButton);
void handleButtonPointing(SDL_Point mousePoint, Button* buttonArr, SDL_Renderer* renderer);
void close(SDL_Renderer* renderer, SDL_Window* window, Button* buttonArr, SDL_Texture* bgTexture);
#endif