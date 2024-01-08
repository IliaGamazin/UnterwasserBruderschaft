#pragma once
#include "Libs.h"
#ifndef WEAPON_H
#define WEAPON_H

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
Weapon createWeapon(WEAPON_TYPE w);
#endif