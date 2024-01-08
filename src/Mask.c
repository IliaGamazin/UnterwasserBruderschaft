#include "Mask.h"
void animMask(SDL_Renderer* r, Mask* m) {
    static double incrementAngle = 1.2;
    static double incrementSize = 1;
    if (m->isAnimated == true)
    {
        if (m->angle > 25.0 || m->angle < -25.0)
        {
            incrementAngle *= -1;
        }
        m->angle += incrementAngle;
        SDL_RenderCopyEx(r, m->maskTextureActive, NULL, &m->maskRect, m->angle, NULL, SDL_FLIP_NONE);
    }
    else {
        m->angle = 0;
        SDL_RenderCopyEx(r, m->maskTextureIdle, NULL, &m->maskRect, m->angle, NULL, SDL_FLIP_NONE);
    }
}
Mask* createMask(SDL_Renderer* r, CHARACTER_TYPE type, int x, int y, int w, int h) {
    Mask* heroMask = (Mask*)malloc(sizeof(Mask));
    heroMask->angle = 0;
    heroMask->isAnimated = false;
    heroMask->maskRect = createRect(x, y, w, h);
    switch (type)
    {
    case SHAYLUSHAY:
        heroMask->maskTextureIdle = IMG_LoadTexture(r, "media/img/masks/shaIdle.png");
        heroMask->maskTextureActive = IMG_LoadTexture(r, "media/img/masks/shaActive.png");
        break;
    case YALTPILS:
        heroMask->maskTextureIdle = IMG_LoadTexture(r, "media/img/masks/yalIdle.png");
        heroMask->maskTextureActive = IMG_LoadTexture(r, "media/img/masks/yalActive.png");
        break;
    case DAWAWUE:
        heroMask->maskTextureIdle = IMG_LoadTexture(r, "media/img/masks/dawIdle.png");
        heroMask->maskTextureActive = IMG_LoadTexture(r, "media/img/masks/dawActive.png");
        break;
    default:
        break;
    }
    return heroMask;
}
Mask** fillMaskArr(SDL_Renderer* r) {
    Mask** maskArr = (Mask**)malloc(3 * sizeof(Mask*));
    maskArr[0] = createMask(r, SHAYLUSHAY, 125, 60, 170, 170);
    maskArr[1] = createMask(r, YALTPILS, 555, 60, 170, 170);
    maskArr[2] = createMask(r, DAWAWUE, 985, 60, 170, 170);
    return maskArr;
}
void destroyMask(Mask* m) {
    SDL_DestroyTexture(m->maskTextureIdle);
    SDL_DestroyTexture(m->maskTextureActive);
    free(m);
}
