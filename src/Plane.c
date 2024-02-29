#include "../inc/Plane.h"
#include "../inc/PlayerLvl3.h"

Enemy *Plane_create(SDL_Renderer* gRenderer) {
    Enemy *plane = (Enemy*)malloc(sizeof(Enemy));

    plane->PlaneRect.x = -200;
    plane->PlaneRect.y = 150;
    plane->PlaneRect.w = PLANE_WIDTH;
    plane->PlaneRect.h = PLANE_HEIGHT;
    plane->pVelX = PLANE_VEL;

    plane->Plane = IMG_LoadTexture(gRenderer, "resource/img/level3/samolet.png");
    plane->PlaneSound = Mix_LoadWAV("resource/sound/plane.wav");

    return plane;
}
void Plane_destroy(Enemy *plane) {
    SDL_DestroyTexture(plane->Plane);
    Mix_FreeChunk(plane->PlaneSound);
    free(plane);
}
void Plane_move(Enemy *plane) {
    plane->PlaneClip.x = 154 * plane->frame;
    plane->PlaneClip.y = 0;
    plane->PlaneClip.w = 154;
    plane->PlaneClip.h = 56;

    if (SDL_GetTicks() % 3 == 0) {
        plane->frame++;
    }
    if (plane->frame >= LVL3PLAYER_FRAMES) {
        plane->frame = 0;
    }
    if ((SDL_GetTicks() >= 10000 && plane->PlaneRect.x <= WINDOW_WIDTH)) {
        plane->PlaneRect.x += plane->pVelX;
        Mix_PlayChannel(-1, plane->PlaneSound, 0);
    }
}
void Plane_show(Enemy *plane, SDL_Renderer* gRenderer) {
    SDL_RenderCopy(gRenderer, plane->Plane, &plane->PlaneClip, &plane->PlaneRect);
}

