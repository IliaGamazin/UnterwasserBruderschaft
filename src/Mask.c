#include "Mask.h"
void animMask(SDL_Renderer* r, Mask* m) {
    static double incrementAngle = 1.2;
    if (m->isAnimated == true)
    {
        if (m->angle > 25.0 || m->angle < -25.0)
        {
            incrementAngle *= -1;
        }
        m->angle += incrementAngle;
        m->maskRect.w = 200;
        m->maskRect.h = 200;
        m->maskRect.y = m->initialY-30;
        SDL_RenderCopyEx(r, m->maskTextureActive, NULL, &m->maskRect, m->angle, NULL, SDL_FLIP_NONE);
    }
    else {
        m->angle = 0;
        m->maskRect.w = 170;
        m->maskRect.h = 170;
        m->maskRect.y = m->initialY;
        SDL_RenderCopyEx(r, m->maskTextureIdle, NULL, &m->maskRect, m->angle, NULL, SDL_FLIP_NONE);
    }
}
Mask* createMask(SDL_Renderer* r, CHARACTER_TYPE type, int x, int y, int w, int h) {
    Mask* heroMask = (Mask*)malloc(sizeof(Mask));
    heroMask->angle = 0;
    heroMask->isAnimated = false;
    heroMask->maskRect = createRect(x, y, w, h);
    heroMask->initialY = y;
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
    maskArr[SHAYLUSHAY] = createMask(r, SHAYLUSHAY, 292, 100, 170, 170);
    maskArr[YALTPILS] = createMask(r, YALTPILS, 552, 100, 170, 170);
    maskArr[DAWAWUE] = createMask(r, DAWAWUE, 818, 100, 170, 170);
    return maskArr;
}
void destroyMask(Mask* m) {
    SDL_DestroyTexture(m->maskTextureIdle);
    SDL_DestroyTexture(m->maskTextureActive);
    free(m);
}
