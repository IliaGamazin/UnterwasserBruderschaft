#include "Header.h"

/*Weapon* createWeapon(type) {
    Weapon* Weapon = (Weapon*);
    switch (type) {
        case RIFLE:
            Weapon->damage = 20;
            Weapon->magSize = 25;
            Weapon->ammoInMag = 25;
            break;
        case SHOTGUN:
            Weapon->damage = 10;        /*Каждая дробинка
            Weapon->magSize = 5;
            Weapon->ammoInMag = 5;
            break;
        case REVOLVER:
            Weapon->damage = 100;
            Weapon->magSize = 6;
            Weapon->ammoInMag = 6;
            break;
    }
    return Weapon;
}*/
Entity* createEntity(int x, int y, int entityWidth, int entityHeight, SDL_Renderer* r ) {
    Entity* Ent = (Entity*)malloc(sizeof(Entity));
    Ent->entityRect = createRect(x, y, entityWidth, entityHeight);
    Ent->entityTex = IMG_LoadTexture(r, "media/img/TEST_CAT.jpg");
    Ent->angle = 0.0;
    return Ent;
}
void showEntity(SDL_Renderer* r, Entity* entity) {
    SDL_RenderCopyEx(r, entity->entityTex, NULL, &entity->entityRect, entity->angle, NULL, SDL_FLIP_NONE);
}
void destroyEntity(Entity* ent) {
    SDL_DestroyTexture(ent->entityTex);
    free(ent);
}


int level1(SDL_Renderer* renderer, SDL_Event event, SDL_Cursor* arrowCursor, SDL_Cursor* handCursor, Mix_Music* bgMusic) {
    Entity* Player = createEntity(640,460, 70, 70, renderer);
    int keyW = 0, keyA = 0, keyS = 0, keyD = 0;
    int run = 1;
    int volume = MAX_VOLUME / 2;
    bgMusic = Mix_LoadMUS("media/sound/nightcall.mp3");
    Mix_PlayMusic(bgMusic, 0);
    
    while (run == 1) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        SDL_Point mousePoint = { mouseX, mouseY };
        double deltaX = mouseX - Player->entityRect.x;
        double deltaY = mouseY - Player->entityRect.y;
        Player->angle = atan2(deltaY, deltaX) * (180.0 / M_PI);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                run = -1;
            } 
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_w:
                    keyW = 1;
                    break;
                case SDLK_a:
                    keyA = 1;
                    break;
                case SDLK_s:
                    keyS = 1;
                    break;
                case SDLK_d:
                    keyD = 1;
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
                    keyW = 0;
                    break;
                case SDLK_a:
                    keyA = 0;
                    break;
                case SDLK_s:
                    keyS = 0;
                    break;
                case SDLK_d:
                    keyD = 0;
                    break;
                }
            }
        }
        if (keyW) {
            Player->entityRect.y -= 4;
        }
        if (keyA) {
            Player->entityRect.x -= 4;
        }
        if (keyS) {
            Player->entityRect.y += 4;
        }
        if (keyD) {
            Player->entityRect.x += 4;
        }

        Player->entityRect.w = volume;
        Player->entityRect.h = volume;
        SDL_RenderClear(renderer);
        showEntity(renderer, Player);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 60);
    }
    destroyEntity(Player);

    SDL_RenderClear(renderer);
    return run;
}