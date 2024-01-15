#include "Header_main.h"


/*void collider(BulletManager* bm, Entity* e) {
    for (int i = 0; i < bm->count; i++)
    {
        SDL_Point currentBulletPoint = { (bm->bullets[i]->bulletRect.x)+(bm->bullets[i]->bulletRect.w / 2),  (bm->bullets[i]->bulletRect.y) + (bm->bullets[i]->bulletRect.h / 2)};
        if (SDL_PointInRect(&currentBulletPoint, &e->entityRect))
        {
            printf("\n A hit!");
        }
    }
}*/

void destroyFirstLevel(Mix_Music* bgMusic, BulletManager* bulletManager, Entity* Player, Tilemap Map, SDL_Texture* ammoTex, SDL_Texture* ammoTexFired) {
    SDL_DestroyTexture(ammoTex);
    SDL_DestroyTexture(ammoTexFired);
    Mix_FreeMusic(bgMusic);
    destroyMap(Map);
    BulletManager_destroy(bulletManager);
    destroyEntity(Player);
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
void showHood(SDL_Renderer* r, Entity* Player, SDL_Texture* ammoTex, SDL_Texture* ammoTexFired){
    SDL_Rect ammoTypeRect = createRect(40, 0, 12, 33);
    for (int i = 0; i < Player->entityWeapon -> ammo_max; i++)
    {
        if (i % 10 == 0)
        {
            ammoTypeRect.x = 40;
            ammoTypeRect.y += 35;
        }
        ammoTypeRect.x += 15;

        if (i < Player->entityWeapon -> ammo)
        {
            SDL_RenderCopy(r, ammoTex, NULL, &ammoTypeRect);
        }
        else{
            SDL_RenderCopy(r, ammoTexFired, NULL, &ammoTypeRect);
        }
                
    }
}
void level1(GameState* PBState, CHARACTER_TYPE CharType) {
    Entity* Player = createEntity(640, 460, 70, 50, PBState->renderer, CharType);
    Tilemap Map = createMap(PBState->renderer);
    BulletManager* bulletManager = BulletManager_new(100);
    ExitCar* Exit = ExitCar_new(PBState->renderer);

    SDL_Texture* ammoTex;
    SDL_Texture* ammoTexFired;

    switch (Player->entityWeapon -> type)
    {
    case RIFLE:
        ammoTex = IMG_LoadTexture(PBState->renderer, "media/img/rifleAmmo.png");
        ammoTexFired = IMG_LoadTexture(PBState->renderer, "media/img/rifleNoAmmo.png");
        break;
    case PISTOL:
        ammoTex = IMG_LoadTexture(PBState->renderer, "media/img/pistolAmmo.png");
        ammoTexFired = IMG_LoadTexture(PBState->renderer, "media/img/pistolNoAmmo.png");
        break;
    case SHOTGUN:
        ammoTex = IMG_LoadTexture(PBState->renderer, "media/img/shotgunAmmo.png");
        ammoTexFired = IMG_LoadTexture(PBState->renderer, "media/img/shotgunNoAmmo.png");
        break;
    }
        
    bool keyW = false, keyA = false, keyS = false, keyD = false;
    int volume = MAX_VOLUME / 2;

    PBState->bgMusic = Mix_LoadMUS("media/sound/nightcall.mp3");
    Mix_PlayMusic(PBState->bgMusic, 0);
    
    while (PBState->run == LEVEL1) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        double deltaX = mouseX - Player->entityRect.x - (Player->entityRect.w / 2);
        double deltaY = mouseY - Player->entityRect.y - (Player->entityRect.h / 2);
        Player->angle = atan2(deltaY, deltaX) * (180.0 / M_PI);
        while (SDL_PollEvent(&PBState->event)) {
            if (PBState->event.type == SDL_QUIT) {
                PBState->run = -1;
            }
            else if (PBState->event.type == SDL_MOUSEBUTTONDOWN && PBState->event.button.button == SDL_BUTTON_LEFT) {
                Vector2 origin = Vector2_new(
                    Player -> entityRect.x,
                    Player -> entityRect.y
                );
                Vector2 direction = Vector2_from_points(
                    origin,
                    Vector2_new(mouseX, mouseY)
                );
                Weapon_shoot(Player -> entityWeapon, bulletManager, origin, direction);
            }
            if (PBState->event.type == SDL_KEYDOWN) {
                switch (PBState->event.key.keysym.sym) {
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
                case SDLK_ESCAPE:
                    PBState->run = MENU;
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
            if (PBState->event.type == SDL_KEYUP) {
                switch (PBState->event.key.keysym.sym) {
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
                case SDLK_r:
                    Exit->isOpened = true;
                    break; 
                }
            }
        }

        if (keyW || keyA || keyS || keyD)
        {
            if (keyW) {
                Player->entityRect.y -= Player->speed;
            }
            if (keyA) {
                Player->entityRect.x -= Player->speed;
            }
            if (keyS) {
                Player->entityRect.y += Player->speed; 
            }  
            if (keyD) {
                Player->entityRect.x += Player->speed;
                
            }
            updateAnim(Player);
        }

        if (Player->reloadingTimer > 0)
        {
            Player->reloadingTimer--;
        }

        SDL_RenderClear(PBState->renderer);
        SDL_Point PlayerCenter = {Player->entityRect.x+Player->entityRect.w/2,Player->entityRect.y+Player->entityRect.h/2};
        ExitCar_update(Exit, PlayerCenter);
        
        if (Exit->isOpened && SDL_PointInRect(&PlayerCenter, &Exit->seatCollider))
        {
            PBState->run = MENU;
        }
        
        BulletManager_update(bulletManager);
        showMap(Map, PBState->renderer);
        BulletManager_render(PBState->renderer, bulletManager);
        showEntity(PBState->renderer, Player);
        ExitCar_render(PBState->renderer, Exit);
        showHood(PBState->renderer, Player, ammoTex, ammoTexFired);
        

        SDL_RenderPresent(PBState->renderer);
        SDL_Delay(1000 / 60);
    }
    destroyFirstLevel(PBState->bgMusic, bulletManager, Player, Map, ammoTex, ammoTexFired);
    SDL_RenderClear(PBState->renderer);
    
}
