#include "Entity.h"
Entity* createEntity(int x, int y, int entityWidth, int entityHeight, SDL_Renderer* r, CHARACTER_TYPE c) {
    Entity* Ent = (Entity*)malloc(sizeof(Entity));
    WEAPON_TYPE w;
    switch (c)
    {
    case SHAYLUSHAY:
        w = RIFLE;
        Ent->entityTex = IMG_LoadTexture(r, "media/img/Shaylushay.png");
        break;
    case DAWAWUE:
        w = SHOTGUN;
        Ent->entityTex = IMG_LoadTexture(r, "media/img/Dawawue.png");
        break;
    case YALTPILS:
        w = PISTOL;
        Ent->entityTex = IMG_LoadTexture(r, "media/img/Yaltpils.png");
        break;
    default:
        break;
    }

    Ent->reloadingTimer = 0;
    Ent->entityWeapon = createWeapon(w);
    Ent->entityRect = createRect(x, y, entityWidth, entityHeight);
    Ent->angle = 0.0;
    Ent->speed = 4;
    return Ent;
}

void destroyEntity(Entity* ent) {
    SDL_DestroyTexture(ent->entityTex);
    Mix_FreeChunk(ent->entityWeapon.shotSound);
    Mix_FreeChunk(ent->entityWeapon.reloadSound);
    free(ent);
}
void showEntity(SDL_Renderer* r, Entity* entity) {
    SDL_RenderCopyEx(r, entity->entityTex, NULL, &entity->entityRect, entity->angle, NULL, SDL_FLIP_NONE);
}

void reload(Entity* Shooter) {
    Mix_PlayChannel(-1, Shooter->entityWeapon.reloadSound, 0);
    Shooter->entityWeapon.ammoInMag += Shooter->entityWeapon.magSize;
    Shooter->entityWeapon.totalAmmoCount -= Shooter->entityWeapon.magSize;
}
