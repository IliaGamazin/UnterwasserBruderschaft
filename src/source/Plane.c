#include "../inc/header.h"

Enemy *Plane_create(SDL_Renderer* gRenderer) {
    Enemy *plane = (Enemy*)malloc(sizeof(Enemy));

    plane->PlaneRect.x = -200;
    plane->PlaneRect.y = 150;
    plane->PlaneRect.w = PLANE_WIDTH;
    plane->PlaneRect.h = PLANE_HEIGHT;
    plane->pVelX = PLANE_VEL;

    plane->Plane = IMG_LoadTexture(gRenderer, "images/samolet.png");
    plane->PlaneSound = Mix_LoadWAV("sound/plane.wav");

    return plane;
}
void Plane_destroy(Enemy *plane) {
    SDL_DestroyTexture(plane->Plane);
    free(plane);
}
void Plane_move(Enemy *plane) {
   for(int i = 0; i < PLAYER_FRAMES; i++) {
        plane->PlaneClip[i].x = 0;
        plane->PlaneClip[i].y = 0;
        plane->PlaneClip[i].w = 169;
        plane->PlaneClip[i].h = 56;
    }

    plane->PlaneRect.x += plane->pVelX;

    if (plane->PlaneRect.x <= SCREEN_WIDTH) {
        Mix_PlayChannel(-1, plane->PlaneSound, 0);
    }
    if (plane->PlaneRect.x >= SCREEN_WIDTH + PLANE_WIDTH) {
        SDL_DestroyTexture(plane->Plane);
    }
}
void Plane_show(Enemy *plane, SDL_Renderer* gRenderer, int frame) {
    SDL_Rect* CurrentClip = &plane->PlaneClip[frame/4];
    SDL_RenderCopy(gRenderer, plane->Plane, CurrentClip, &plane->PlaneRect);
}
