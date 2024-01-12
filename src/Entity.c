#include "Entity.h"
Entity* createEntity(int x, int y, int entityWidth, int entityHeight, SDL_Renderer* r, CHARACTER_TYPE c) {
    Entity* Ent = (Entity*)malloc(sizeof(Entity));
    WEAPON_TYPE w;
    switch (c)
    {
    case SHAYLUSHAY:
        w = RIFLE;
        Ent->entityTex = IMG_LoadTexture(r, "media/img/shailushit.png");
        break;
    case DAWAWUE:
        w = SHOTGUN;
        Ent->entityTex = IMG_LoadTexture(r, "media/img/shailushit.png");
        break;
    case YALTPILS:
        w = PISTOL;
        Ent->entityTex = IMG_LoadTexture(r, "media/img/shailushit.png");
        break;
    default:
        break;
    }

    Ent->reloadingTimer = 0;
    Ent->entityWeapon = createWeapon(w);
    Ent->entityRect = createRect(x, y, entityWidth, entityHeight);
    Ent->currentClip = createRect(Ent->entityWeapon.type * 85, Ent->currentClipFrame * 66, entityWidth, entityHeight);
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

void updateAnim(Entity* entity){
    static Uint32 lastUpdateTime = 0;
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime-lastUpdateTime>=180)
    {
        entity->currentClip.x = entity->entityWeapon.type * 85;
        entity->currentClip.y = entity->currentClipFrame * 66;
        entity->currentClipFrame++;
        if (entity->currentClipFrame > 2)
        {
            entity->currentClipFrame  = 0;
        }
        lastUpdateTime = currentTime;
    }
}

void showEntity(SDL_Renderer* r, Entity* entity) {
    SDL_RenderCopyEx(r, entity->entityTex, &entity->currentClip, &entity->entityRect, entity->angle, NULL, SDL_FLIP_NONE);
}

void reload(Entity* Shooter) {
    Mix_PlayChannel(-1, Shooter->entityWeapon.reloadSound, 0);
    Shooter->entityWeapon.ammoInMag += Shooter->entityWeapon.magSize;
}
