#include "Bullet.h"
Bullet* createBullet(int x, int y, double angle, SDL_Renderer* r) {
    double angleError = (rand() % (2 * BULLET_MISS_MODIFIER + 1) - BULLET_MISS_MODIFIER);
    Bullet* Bul = (Bullet*)malloc(sizeof(Bullet));
    Bul->bulletRect = createRect(x, y, BULLET_SIZE, BULLET_SIZE);
    Bul->velocity = BULLET_SPEED + rand() % 11;
    Bul->angle = angle + angleError;
    Bul->bulletTex = IMG_LoadTexture(r, "media/img/bullet.png");
    return Bul;
}
void updateBullet(Bullet* bullet) {
    bullet->bulletRect.x += (int)(bullet->velocity * cos(bullet->angle * (M_PI / 180.0)));
    bullet->bulletRect.y += (int)(bullet->velocity * sin(bullet->angle * (M_PI / 180.0)));
}
void showBullet(SDL_Renderer* r, Bullet* bullet) {
    SDL_RenderCopyEx(r, bullet->bulletTex, NULL, &bullet->bulletRect, bullet->angle, NULL, SDL_FLIP_NONE);
}
void destroyBullet(Bullet* bullet) {
    SDL_DestroyTexture(bullet->bulletTex);
    free(bullet);
}