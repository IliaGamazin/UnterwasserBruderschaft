#include "Weapon.h"
Weapon createWeapon(WEAPON_TYPE w) {
    Weapon Weap;
    switch (w)
    {
    case RIFLE:
        Weap.damage = 25;
        Weap.ammoInMag = 20;
        Weap.magSize = 20;
        Weap.reloadMagTime = 100; 
        Weap.reloadRoundTime = 10;
        Weap.totalAmmoCount = 80;
        Weap.type = RIFLE;
        Weap.shotSound = Mix_LoadWAV("media/sound/rifleShot.wav");
        Weap.reloadSound = Mix_LoadWAV("media/sound/rifleReload.wav");
        Weap.bulletsNum = 1;
        break;
    case SHOTGUN:
        Weap.damage = 30;
        Weap.ammoInMag = 6;
        Weap.magSize = 6;
        Weap.reloadMagTime = 140; 
        Weap.reloadRoundTime = 60;
        Weap.totalAmmoCount = 18;
        Weap.type = SHOTGUN;
        Weap.shotSound = Mix_LoadWAV("media/sound/shotgunShot.wav");
        Weap.reloadSound = Mix_LoadWAV("media/sound/shotgunReload.wav");
        Weap.bulletsNum = 4;
        break;
    case PISTOL:
        Weap.damage = 100;
        Weap.ammoInMag = 6;
        Weap.magSize = 6;
        Weap.reloadMagTime = 120; 
        Weap.reloadRoundTime = 40;
        Weap.totalAmmoCount = 12;
        Weap.type = PISTOL;
        Weap.shotSound = Mix_LoadWAV("media/sound/shotgunShot.wav");
        Weap.reloadSound = Mix_LoadWAV("media/sound/shotgunReload.wav");
        Weap.bulletsNum = 1;
        break;
    default:
        break;
    }
    return Weap;
}
