#include "Header.h"

Weapon createWeapon(enum WEAPON_TYPE w) {
    Weapon Weap;
    switch (w)
    {
    case RIFLE:
        Weap.damage = 25;
        Weap.ammoInMag = 20;
        Weap.magSize = 20;
        Weap.reloadMagTime = 100; //Кадров
        Weap.reloadRoundTime = 10;
        Weap.totalAmmoCount = 80;
        Weap.type = RIFLE;
        Weap.shotSound = Mix_LoadWAV("media/sound/rifleShot.wav");
        Weap.reloadSound = Mix_LoadWAV("media/sound/rifleReload.wav");
        Weap.bulletsNum = 1;
        break;
    case SHOTGUN:
        Weap.damage = 30;
        Weap.ammoInMag = 6;
        Weap.magSize = 6;
        Weap.reloadMagTime = 140; //Кадров
        Weap.reloadRoundTime = 60;
        Weap.totalAmmoCount = 18;
        Weap.type = SHOTGUN;
        Weap.shotSound = Mix_LoadWAV("media/sound/shotgunShot.wav");
        Weap.reloadSound = Mix_LoadWAV("media/sound/shotgunReload.wav");
        Weap.bulletsNum = 6;
        break;
    case REVOLVER:
        Weap.damage = 100;
        Weap.ammoInMag = 6;
        Weap.magSize = 6;
        Weap.reloadMagTime = 120; //Кадров
        Weap.reloadRoundTime = 40;
        Weap.totalAmmoCount = 12;
        Weap.type = REVOLVER;
        Weap.shotSound = Mix_LoadWAV("media/sound/shotgunShot.wav");
        Weap.reloadSound = Mix_LoadWAV("media/sound/shotgunReload.wav");
        Weap.bulletsNum = 1;
        break;
    default:
        break;
    }
    return Weap;
}

Entity* createEntity(int x, int y, int entityWidth, int entityHeight, SDL_Renderer* r, enum WEAPON_TYPE w) {
    Entity* Ent = (Entity*)malloc(sizeof(Entity));
    Ent->reloadingTimer = 0;
    Ent->entityWeapon = createWeapon(w);
    Ent->entityRect = createRect(x, y, entityWidth, entityHeight);
    Ent->entityTex = IMG_LoadTexture(r, "media/img/TEST_CAT.jpg");
    Ent->angle = 0.0;
    Ent->speed = 4;
    return Ent;
}

Bullet* createBullet(int x, int y, double angle, SDL_Renderer* r) {
    double angleError = (rand() % (2 * BULLET_MISS_MODIFIER + 1) - BULLET_MISS_MODIFIER);
    Bullet* Bul = (Bullet*)malloc(sizeof(Bullet));
    Bul->bulletRect = createRect(x, y, BULLET_SIZE, BULLET_SIZE);
    Bul->velocity = BULLET_SPEED;
    Bul->angle = angle + angleError;
    Bul->bulletTex = IMG_LoadTexture(r, "media/img/bullet.png");
    return Bul;
}

BulletManager* createBulletManager(int capacity) {
    BulletManager* bulletManager = (BulletManager*)malloc(sizeof(BulletManager));
    bulletManager->bullets = (Bullet**)malloc(capacity * sizeof(Bullet*));
    bulletManager->capacity = capacity;
    bulletManager->count = 0;
    return bulletManager;
}
void destroyEntity(Entity* ent) {
    SDL_DestroyTexture(ent->entityTex);
    Mix_FreeChunk(ent->entityWeapon.shotSound);
    Mix_FreeChunk(ent->entityWeapon.reloadSound);
    free(ent);
}
void destroyBullet(Bullet* bullet) {
    SDL_DestroyTexture(bullet->bulletTex);
    free(bullet);
}
void destroyBulletManager(BulletManager* bulletManager) {
    for (int i = 0; i < bulletManager->count; ++i) {
        destroyBullet(bulletManager->bullets[i]);
    }
    free(bulletManager->bullets);
    free(bulletManager);
}
void destroyCollidedBullet(BulletManager* bulletManager, int index) {
    destroyBullet(bulletManager->bullets[index]);
    if (index < bulletManager->count - 1) {
        bulletManager->bullets[index] = bulletManager->bullets[bulletManager->count - 1];
    }
    --bulletManager->count;
}

void spawnBullet(BulletManager* bulletManager, Entity* Shooter, SDL_Renderer* r) {
    if (bulletManager->count < bulletManager->capacity) {
        int spawnX = Shooter->entityRect.x + Shooter->entityRect.w / 2- BULLET_SIZE / 2;
        int spawnY = Shooter->entityRect.y + Shooter->entityRect.h / 2- BULLET_SIZE / 2;

        Bullet* newBullet = createBullet(spawnX, spawnY, Shooter->angle, r);
        bulletManager->bullets[bulletManager->count++] = newBullet;
    }
}
void updateBullet(Bullet* bullet) {
    bullet->bulletRect.x += (int)(bullet->velocity * cos(bullet->angle * (M_PI / 180.0)));
    bullet->bulletRect.y += (int)(bullet->velocity * sin(bullet->angle * (M_PI / 180.0)));
}
void updateBulletManager(BulletManager* bulletManager) {
    for (int i = 0; i < bulletManager->count; ++i) {
        updateBullet(bulletManager->bullets[i]);
        if (bulletManager->bullets[i]->bulletRect.x < 0 || bulletManager->bullets[i]->bulletRect.x > 1280 ||
            bulletManager->bullets[i]->bulletRect.y < 0 || bulletManager->bullets[i]->bulletRect.y > 720) {
            destroyCollidedBullet(bulletManager, i);
            --i;  
        }
    }
}
void showEntity(SDL_Renderer* r, Entity* entity) {
    SDL_RenderCopyEx(r, entity->entityTex, NULL, &entity->entityRect, entity->angle, NULL, SDL_FLIP_NONE);
}

void showBullet(SDL_Renderer* r, Bullet* bullet) {
    SDL_RenderCopyEx(r, bullet->bulletTex, NULL, &bullet->bulletRect, bullet->angle, NULL, SDL_FLIP_NONE);
}
void showAllBullets(SDL_Renderer* r, BulletManager* bulletManager) {
    for (int i = 0; i < bulletManager->count; ++i) {
        showBullet(r, bulletManager->bullets[i]);
    }
}
void shoot(BulletManager* bulletManager, Entity* Shooter, SDL_Renderer* r) {
    for (int i = 0; i < Shooter->entityWeapon.bulletsNum; i++)
    {
        spawnBullet(bulletManager, Shooter, r);
    }
    Shooter->entityWeapon.ammoInMag--;
    Mix_PlayChannel(-1, Shooter->entityWeapon.shotSound, 0);
}
void reload(Entity* Shooter) {
    Shooter->entityWeapon.ammoInMag += Shooter->entityWeapon.magSize;
    Shooter->entityWeapon.totalAmmoCount -= Shooter->entityWeapon.magSize;
    Mix_PlayChannel(-1, Shooter->entityWeapon.reloadSound, 0);
}
/*void handleShooting(SDL_Renderer* r, SDL_Event e, BulletManager* bulletManager, Entity* Shooter) {
    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        if (Shooter->entityWeapon.ammoInMag > 0 && Shooter->reloadingTimer == 0)
        {
            printf("\nShot!");
            shoot(bulletManager, Shooter, r);
            Shooter->reloadingTimer = Shooter->entityWeapon.reloadRoundTime;
        }
        if (Shooter->entityWeapon.ammoInMag == 0 && Shooter->entityWeapon.totalAmmoCount != 0)
        {
            Shooter->reloadingTimer = Shooter->entityWeapon.reloadMagTime;
            reload(Shooter);
        }
    }
    if (Shooter->reloadingTimer > 0)
    {
        Shooter->reloadingTimer--;
    }
}*/

int level1(SDL_Renderer* renderer, SDL_Event event, SDL_Cursor* arrowCursor, SDL_Cursor* handCursor, Mix_Music* bgMusic) {
    SDL_Texture* bgTexture;
    SDL_Rect bgRect;
    bool keyW = false, keyA = false, keyS = false, keyD = false;
    int run = LEVEL1;

    int volume = MAX_VOLUME / 2;
    bgMusic = Mix_LoadMUS("media/sound/nightcall.mp3");
    Mix_PlayMusic(bgMusic, 0);

    Entity* Player = createEntity(640, 460, 70, 70, renderer, RIFLE);
    BulletManager* bulletManager = createBulletManager(100);
    while (run == LEVEL1) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        SDL_Point mousePoint = { mouseX, mouseY };
        double deltaX = mouseX - Player->entityRect.x - (Player->entityRect.w / 2);
        double deltaY = mouseY - Player->entityRect.y - (Player->entityRect.h / 2);
        Player->angle = atan2(deltaY, deltaX) * (180.0 / M_PI);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                run = -1;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                if (Player->entityWeapon.ammoInMag > 0 && Player->reloadingTimer == 0 )
                {
                    shoot(bulletManager, Player, renderer);
                    Player->reloadingTimer = Player->entityWeapon.reloadRoundTime;
                }
                if (Player->entityWeapon.ammoInMag == 0 && Player->entityWeapon.totalAmmoCount!=0)
                {
                    Player->reloadingTimer = Player->entityWeapon.reloadMagTime;
                    reload(Player);
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_w:
                    keyW = true;
                    break;
                case SDLK_a:
                    keyA = true;
                    break;
                case SDLK_s:
                    keyS = true;
                    break;
                case SDLK_d:
                    keyD = true;
                    break;
                case SDLK_r:
                    break;
                case SDLK_ESCAPE:
                    run = 0;
                    break;
                case SDLK_EQUALS:
                    printf("\n Volume: %d", volume);
                    if (volume < MAX_VOLUME) {
                        volume += MAX_VOLUME / 10;
                    }
                    else {
                        volume = MAX_VOLUME;
                    }
                    break;
                case SDLK_MINUS:
                    printf("\n Volume: %d", volume);
                    if (volume > 0) {
                        volume -= MAX_VOLUME / 10;
                    }
                    else {
                        volume = 0;
                    }
                    break;
                }
                Mix_Volume(-1, volume);
                Mix_VolumeMusic(volume);
            }
            else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                case SDLK_w:
                    keyW = false;
                    break;
                case SDLK_a:
                    keyA = false;
                    break;
                case SDLK_s:
                    keyS = false;
                    break;
                case SDLK_d:
                    keyD = false;
                    break;
                }
            }
        }
        if (keyW ) {
            Player->entityRect.y -= Player->speed;
        }
        if (keyA ) {
            Player->entityRect.x -= Player->speed;
        }
        if (keyS ) {
            Player->entityRect.y += Player->speed;
        }
        if (keyD) {
            Player->entityRect.x += Player->speed;
        }

        if (Player->reloadingTimer >0)
        {
            Player->reloadingTimer--;
        }

        SDL_RenderClear(renderer);
        showAllBullets(renderer, bulletManager);
        showEntity(renderer, Player);
        SDL_RenderPresent(renderer);
        updateBulletManager(bulletManager);
        SDL_Delay(1000 / 60);
    }
    destroyBulletManager(bulletManager);
    destroyEntity(Player);
    SDL_RenderClear(renderer);
    return run;
}