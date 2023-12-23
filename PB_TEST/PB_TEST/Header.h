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
#include <math.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define BUTTON_COUNT 5
#define BUTTON_HEIGHT 60
#define BUTTON_WIDTH 150
#define BUTTON_GAP 100

#define BULLET_SIZE 15
#define BULLET_SPEED  20
#define BULLET_MISS_MODIFIER 10
#define MAX_VOLUME 120


enum SCENE {
    MENU,
    INTRO,
    LEVEL1,
    LEVEL2,
    LEVEL3,
    LEVEL_SECRET,
    OUTRO
};

enum BUTTON_TYPE {
    START_BUTTON,
    FIRST_LEVEL_BUTTON,
    SECOND_LEVEL_BUTTON,
    THIRD_LEVEL_BUTTON,
    EXIT_BUTTON
};

enum WEAPON_TYPE {
    RIFLE,
    SHOTGUN,
    REVOLVER
};

typedef struct {
    int velocity;
    double angle;
    SDL_Rect bulletRect;
    SDL_Texture* bulletTex;
}Bullet;

typedef struct {
    Bullet** bullets;  
    int capacity;      
    int count;         
} BulletManager;

typedef struct {
    int damage;
    int magSize;
    int ammoInMag;
    int reloadRoundTime;
    int reloadMagTime;
    int totalAmmoCount;
    int type;
    int bulletsNum;
    Mix_Chunk* shotSound;
    Mix_Chunk* reloadSound;
}Weapon;

typedef struct{
    int reloadingTimer;
    int speed;
    double angle;
    SDL_Rect entityRect;
    Weapon entityWeapon;
    SDL_Texture* entityTex;
}Entity;

typedef struct {
    SDL_Rect buttonRect;
    SDL_Texture* buttonTexIdle;
    SDL_Texture* buttonTexHover;
    Mix_Chunk* buttonSound;
    bool isPointedAt;
    bool isPlayingSound;
}Button;

typedef struct {
    SDL_Rect barRect;
    SDL_Texture* barTexture;
}SoundBar;

SDL_Rect createRect(int x, int y, int rectWidth, int rectHeight);
Button createButton(int x, int y, int buttonWidth, int buttonHeight, SDL_Texture* buttonTexIdle, SDL_Texture* buttonTexHover, Mix_Chunk* buttonSound);
Button* fillButtonArr(int x, int y, int buttonWidth, int buttonHeight, SDL_Renderer* r);
SoundBar* createSoundBar(int x, int y, int barWidth, int barHeight, SDL_Renderer* r);

Entity* createEntity(int x, int y, int entityWidth, int entityHeight, SDL_Renderer* r, enum WEAPON_TYPE w);
Bullet* createBullet(int x, int y, double angle, SDL_Renderer* r);
BulletManager* createBulletManager(int capacity);

void destroyButton(Button b);
void destroyBar(SoundBar* b);

void destroyBullet(Bullet* b);
void destroyEntity(Entity* ent);
void destroyBulletManager(BulletManager* bulletManager);
void destroyCollidedBullet(BulletManager* bulletManager, int index);

void destroyMenu(Button* buttonArr, SDL_Texture* bgTexture, SoundBar* Bar, Mix_Music* bgMusic, Mix_Chunk* exitSound);

void destroyWindow(SDL_Renderer* r, SDL_Window* window, SDL_Cursor* arrow, SDL_Cursor* hand);

int menu(SDL_Renderer* renderer, SDL_Event event, SDL_Cursor* arrowCursor, SDL_Cursor* handCursorm, Mix_Music* bgMusic);
int level1(SDL_Renderer* renderer, SDL_Event event, SDL_Cursor* arrowCursor, SDL_Cursor* handCursor, Mix_Music* bgMusic);

void updateSoundBar(SoundBar* soundBar, int volume);

void showButton(SDL_Renderer* r, Button button);

void showEntity(SDL_Renderer* r, Entity* entity);
void showBullet(SDL_Renderer* r, Bullet* bullet);
void showAllBullets(SDL_Renderer* r, BulletManager* bulletManager);
void reload(Entity* Shooter);
void shoot(BulletManager* bulletManager, Entity* Shooter, SDL_Renderer* r);

void handleButtonPointing(SDL_Point mousePoint, Button* buttonArr, SDL_Renderer* r, SDL_Cursor* arrowCursor, SDL_Cursor* handCursor);

void spawnBullet(BulletManager* bulletManager, Entity* Shooter, SDL_Renderer* r);
void updateBullet(Bullet* bullet);
void updateBulletManager(BulletManager* bulletManager);


#endif