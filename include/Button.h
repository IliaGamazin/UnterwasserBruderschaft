#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "./Libs.h"

typedef struct {
    SDL_Rect button_rect;
    SDL_Texture *button_tex_idle;
    SDL_Texture *button_tex_hover;
    Mix_Chunk *button_sound;
    bool hower;
    bool playing_sound;
} Button;

Button Button_new(int x, int y, int w, int h, SDL_Texture *button_tex_idle, SDL_Texture *button_tex_hover, Mix_Chunk *buttonSound);
Button *Button_arr_new_choose(SDL_Renderer *r);
Button *Button_arr_new_menu(int x, int y, int w, int h, SDL_Renderer *r);
void Button_render(SDL_Renderer *r, Button button);
void Button_destroy(Button b);

#endif

