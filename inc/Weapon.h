#pragma once
#ifndef WEAPON_H
#define WEAPON_H

#include "./Libs.h"
#include "./BulletManager.h"
#include "./Vector.h"

// WEAPON_TYPE

typedef enum {
    RIFLE,
    PISTOL,
    SHOTGUN,
} WEAPON_TYPE;

// Weapon

typedef struct {
    WEAPON_TYPE type;
    uint32_t ammo_max;
    uint32_t ammo;
    uint32_t bullets_num;
    uint32_t last_shoot;
    uint32_t round_delay;
    Mix_Chunk *shot_sound;
    Mix_Chunk *no_ammo_sound;
} Weapon;

Weapon *Weapon_new(WEAPON_TYPE type);
void Weapon_destroy(Weapon *weapon);
void Weapon_shoot(Weapon *weapon, BulletManager *bullet_manager, Vector2 oririn, Vector2 direction, bool is_player);

#endif

