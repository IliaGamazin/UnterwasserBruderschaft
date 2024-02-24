#include "../inc/Mask.h"

// Mask

Mask *Mask_new(SDL_Renderer *r, CHARACTER_TYPE type, int x, int y, int w, int h) {
    Mask* heroMask = (Mask*)malloc(sizeof(Mask));
    heroMask->angle = 0;
    heroMask->is_animated = false;
    heroMask->mask_rect = Rect_new(x, y, w, h);
    heroMask->init_y = y;

    switch (type) {
        case SHAYLUSHAY:
            heroMask->mask_tex_idle = IMG_LoadTexture(r, "media/img/masks/shaIdle.png");
            heroMask->mask_tex_active = IMG_LoadTexture(r, "media/img/masks/shaActive.png");
            break;
        case YALTPILS:
            heroMask->mask_tex_idle = IMG_LoadTexture(r, "media/img/masks/yalIdle.png");
            heroMask->mask_tex_active = IMG_LoadTexture(r, "media/img/masks/yalActive.png");
            break;
        case DAWAWUE:
            heroMask->mask_tex_idle = IMG_LoadTexture(r, "media/img/masks/dawIdle.png");
            heroMask->mask_tex_active = IMG_LoadTexture(r, "media/img/masks/dawActive.png");
            break;
    }

    return heroMask;
}

void Mask_render(SDL_Renderer *r, Mask* m) {
    static double angle_inc = 1.2;

    if (m->is_animated) {
        if (m->angle > 25.0 || m->angle < -25.0) {
            angle_inc *= -1;
        }
        m->angle += angle_inc;
        m->mask_rect.w = 200;
        m->mask_rect.h = 200;
        m->mask_rect.y = m->init_y - 30;
        SDL_RenderCopyEx(r, m->mask_tex_active, NULL, &m->mask_rect, m->angle, NULL, SDL_FLIP_NONE);
    }
    else {
        m->angle = 0;
        m->mask_rect.w = 170;
        m->mask_rect.h = 170;
        m->mask_rect.y = m->init_y;
        SDL_RenderCopyEx(r, m->mask_tex_idle, NULL, &m->mask_rect, m->angle, NULL, SDL_FLIP_NONE);
    }
}

Mask **Mask_arr_new(SDL_Renderer *r) {
    Mask **mask_arr = (Mask**)malloc(3 * sizeof(Mask*));
    mask_arr[SHAYLUSHAY] = Mask_new(r, SHAYLUSHAY, 292, 100, 170, 170);
    mask_arr[YALTPILS] = Mask_new(r, YALTPILS, 552, 100, 170, 170);
    mask_arr[DAWAWUE] = Mask_new(r, DAWAWUE, 818, 100, 170, 170);
    return mask_arr;
}

void Mask_destroy(Mask *m) {
    SDL_DestroyTexture(m->mask_tex_idle);
    SDL_DestroyTexture(m->mask_tex_active);
    free(m);
}

