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

void destroyFirstLevel(Mix_Music* bgMusic, BulletManager* bulletManager, Entity* Player) {
    Mix_FreeMusic(bgMusic);
    destroyBulletManager(bulletManager);
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

void level1(GameState* PBState) {
    levelIntro(PBState, LEVEL1);
    if (PBState->run == LEVEL1_CHOOSE)
    {
        Entity** targets;
        targets = (Entity**)malloc(2 * sizeof(Entity*));
        targets[0] = createEntity(0, 0, 100, 100, PBState->renderer, SHAYLUSHAY);
        targets[1] = createEntity(0, 300, 100, 100, PBState->renderer, SHAYLUSHAY);
        Entity* Player = createEntity(640, 460, 70, 70, PBState->renderer, chooseCharacter(PBState, LEVEL1));
        bool keyW = false, keyA = false, keyS = false, keyD = false;
        int volume = MAX_VOLUME / 2;
        PBState->bgMusic = Mix_LoadMUS("media/sound/nightcall.mp3");
        Mix_PlayMusic(PBState->bgMusic, 0);

        BulletManager* bulletManager = createBulletManager(100);
        while (PBState->run == LEVEL1) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            SDL_Point mousePoint = { mouseX, mouseY };
            double deltaX = mouseX - Player->entityRect.x - (Player->entityRect.w / 2);
            double deltaY = mouseY - Player->entityRect.y - (Player->entityRect.h / 2);
            Player->angle = atan2(deltaY, deltaX) * (180.0 / M_PI);
            while (SDL_PollEvent(&PBState->event)) {
                if (PBState->event.type == SDL_QUIT) {
                    PBState->run = -1;
                }
                else if (PBState->event.type == SDL_MOUSEBUTTONDOWN && PBState->event.button.button == SDL_BUTTON_LEFT) {
                    if (Player->entityWeapon.ammoInMag > 0 && Player->reloadingTimer == 0)
                    {
                        shoot(bulletManager, Player, PBState->renderer);
                        Player->reloadingTimer = Player->entityWeapon.reloadRoundTime;
                    }
                    if (Player->entityWeapon.ammoInMag == 0 && Player->entityWeapon.totalAmmoCount != 0)
                    {
                        Player->reloadingTimer = Player->entityWeapon.reloadMagTime;
                        reload(Player);
                    }
                }
                else if (PBState->event.type == SDL_KEYDOWN) {
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
                    case SDLK_r:
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
                else if (PBState->event.type == SDL_KEYUP) {
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
                    }
                }
            }
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

            if (Player->reloadingTimer > 0)
            {
                Player->reloadingTimer--;
            }
           // collider(bulletManager, targets[0]);
         //   collider(bulletManager, targets[1]);
            SDL_RenderClear(PBState->renderer);
            showAllBullets(PBState->renderer, bulletManager);
            showEntity(PBState->renderer, Player);
            showEntity(PBState->renderer, targets[0]);
            showEntity(PBState->renderer, targets[1]);
            SDL_RenderPresent(PBState->renderer);
            updateBulletManager(bulletManager);
            
            SDL_Delay(1000 / 60);
        }
        destroyFirstLevel(PBState->bgMusic, bulletManager, Player);
        SDL_RenderClear(PBState->renderer);
    }
}