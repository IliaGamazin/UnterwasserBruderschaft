#include "./Weapon.h"

// Weapon

Weapon *Weapon_new(WEAPON_TYPE type) {
    Weapon *weapon = malloc(sizeof(Weapon));
    weapon -> last_shoot = 0;
    weapon -> no_ammo_sound = Mix_LoadWAV("media/sound/no_ammo.wav");

    switch (type) {
        case RIFLE:
            weapon -> type = RIFLE;
            weapon -> ammo_max = 60;
            weapon -> ammo = weapon -> ammo_max;
            weapon -> bullets_num = 1;
            weapon -> round_delay = 170;
            weapon -> shot_sound = Mix_LoadWAV("media/sound/rifleShot.wav");
            break;
        case SHOTGUN:
            weapon -> type = RIFLE;
            weapon -> ammo_max = 18;
            weapon -> ammo = weapon -> ammo_max;
            weapon -> bullets_num = 4;
            weapon -> round_delay = 1000;
            weapon -> shot_sound = Mix_LoadWAV("media/sound/shotgunShot.wav");
            break;
        case PISTOL:
            weapon -> type = RIFLE;
            weapon -> ammo_max = 24;
            weapon -> ammo = weapon -> ammo_max;
            weapon -> bullets_num = 1;
            weapon -> round_delay = 600;
            weapon -> shot_sound = Mix_LoadWAV("media/sound/shotgunShot.wav");
            break;
    }

    return weapon;
}

void Weapon_destroy(Weapon *weapon) {
    Mix_FreeChunk(weapon -> shot_sound);
    Mix_FreeChunk(weapon -> no_ammo_sound);
    free(weapon);
}

void Weapon_shoot(Weapon *weapon, BulletManager *bullet_manager, Vector2 origin, Vector2 direction) {
    if (SDL_GetTicks() <= weapon -> last_shoot + weapon -> round_delay) {
        return;
    }

    if (!weapon -> ammo) {
        Mix_PlayChannel(-1, weapon -> no_ammo_sound, 0);
        return;
    }

    Mix_PlayChannel(-1, weapon -> shot_sound, 0);

    for (size_t i = 0; i < weapon -> bullets_num; i++) {
        BulletManager_add(
            bullet_manager,
            Bullet_new(
                origin,
                Vector2_rotated(direction, degrees_to_radians((rand() / (double) RAND_MAX * 6) - 3)), // Random direction rotation by [-3; 3] degrees
                30,
                Rgba_new(255, 255, 255, 255)
            )
        );
    }

    bullet_manager -> count++;
    weapon -> ammo--;
    weapon -> last_shoot = SDL_GetTicks();
}

