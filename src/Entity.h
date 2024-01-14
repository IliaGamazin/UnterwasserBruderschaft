#pragma once
#include "Weapon.h"
#ifndef ENTITY_H
#define ENTITY_H

typedef struct {
    int reloadingTimer;
    int speed;
    int currentClipFrame;
    double angle;
    SDL_Rect entityRect;
    SDL_Rect currentClip;
    Weapon *entityWeapon;
    SDL_Texture* entityTex;
}Entity;

Entity* createEntity(int x, int y, int entityWidth, int entityHeight, SDL_Renderer* r, CHARACTER_TYPE c);
void updateAnim(Entity* entity);
void showEntity(SDL_Renderer* r, Entity* entity);
void destroyEntity(Entity* ent);
void reload(Entity* Shooter);
#endif
