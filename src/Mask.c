#include "../inc/Mask.h"

// Mask

Mask *Mask_new(SDL_Renderer *r, CHARACTER_TYPE type, int x, int y, int w, int h) {
    Mask* hero_mask = (Mask*)malloc(sizeof(Mask));

    hero_mask->is_animated = false;
    hero_mask->mask_rect = Rect_new(x, y, w, h);

    hero_mask->init_y = y;
    hero_mask->init_height = 170;
    hero_mask->init_width = 170;

    hero_mask->angle_inc = 1.2;
    hero_mask->angle = 0;
    hero_mask->angle_limit = 25.0;

    switch (type) {
        case SHAYLUSHAY:
            hero_mask->mask_tex_idle = IMG_LoadTexture(r, "./resource/img/masks/shaIdle.png");
            hero_mask->mask_tex_active = IMG_LoadTexture(r, "./resource/img/masks/shaActive.png");
            break;
        case YALTPILS:
            hero_mask->mask_tex_idle = IMG_LoadTexture(r, "./resource/img/masks/yalIdle.png");
            hero_mask->mask_tex_active = IMG_LoadTexture(r, "./resource/img/masks/yalActive.png");
            break;
        case DAWAWUE:
            hero_mask->mask_tex_idle = IMG_LoadTexture(r, "./resource/img/masks/dawIdle.png");
            hero_mask->mask_tex_active = IMG_LoadTexture(r, "./resource/img/masks/dawActive.png");
            break;
    }

    return hero_mask;
}

Mask *Mask_gameover_new(SDL_Renderer *r) {
    Mask *hero_mask = (Mask*)malloc(sizeof(Mask));

    hero_mask->angle_limit = 2.0;
    hero_mask->angle_inc = 0.1;
    hero_mask->angle = 0;

    hero_mask->is_animated = false;

    hero_mask->mask_rect = Rect_new(370, 100, 300, 75);
    hero_mask->init_y = 100;
    hero_mask->init_width = 541;
    hero_mask->init_height = 173;

    hero_mask->mask_tex_idle = IMG_LoadTexture(r, "./resource/img/gameover/zrada.png");
    hero_mask->mask_tex_active = IMG_LoadTexture(r, "./resource/img/gameover/zrada.png");

    return hero_mask;
}

void Mask_render(SDL_Renderer *r, Mask* m) {

    if (m->is_animated) {
        if (m->angle > m->angle_limit || m->angle < -m->angle_limit) {
            m->angle_inc *= -1;
        }

        m->angle += m->angle_inc;
        m->mask_rect.w = m->init_width + 30;
        m->mask_rect.h = m->init_height + 30;
        m->mask_rect.y = m->init_y - 30;
        SDL_RenderCopyEx(r, m->mask_tex_active, NULL, &m->mask_rect, m->angle, NULL, SDL_FLIP_NONE);
    }

    else {
        m->angle = 0;
        m->mask_rect.w = m->init_width;
        m->mask_rect.h = m->init_height;
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

