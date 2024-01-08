#pragma once
#include "Libs.h"
#ifndef BULLET_H
#define BULLET_H

typedef struct {
    int velocity;
    double angle;
    SDL_Rect bulletRect;
    SDL_Texture* bulletTex;
}Bullet;

Bullet* createBullet(int x, int y, double angle, SDL_Renderer* r);
void showBullet(SDL_Renderer* r, Bullet* bullet);
void updateBullet(Bullet* bullet);
void destroyBullet(Bullet* b);

#endif
