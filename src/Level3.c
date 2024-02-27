#include "../inc/Header_main.h"

void  level3 (GameState *PBState) {
    Mix_Music* gBGMusic = Mix_LoadMUS("resource/sound/bgm.wav");

    SDL_Texture* gMap[BACKGROUNDS];
    SDL_Rect g_map;

    gMap[0] = IMG_LoadTexture(PBState->renderer, "resource/img/level3/fon1.png");
    gMap[1] = IMG_LoadTexture(PBState->renderer, "resource/img/level3/fon2.png");
    gMap[2] = IMG_LoadTexture(PBState->renderer, "resource/img/level3/fon3.png");
    gMap[3] = IMG_LoadTexture(PBState->renderer, "resource/img/level3/fon4.png");
    gMap[4] = IMG_LoadTexture(PBState->renderer, "resource/img/level3/fon5.png");
    gMap[5] = IMG_LoadTexture(PBState->renderer, "resource/img/level3/fon6.png");
    gMap[6] = IMG_LoadTexture(PBState->renderer, "resource/img/level3/fon7.png");

    int volume = MAX_VOLUME / 2;

    Mix_PlayMusic(gBGMusic, -1);

    g_map.w = WINDOW_WIDTH;
    g_map.h = WINDOW_HEIGHT;
    g_map.x = 0;
    g_map.y = 0;

    int backgr = 0;
    int bcat = 0;

    PlayerSecretLvL* player = Player_create(PBState->renderer);
    Enemy* plane = Plane_create(PBState->renderer);
    Counter* counter = Counter_create(PBState->renderer);
    CatManager* catManager = CatManager_create(10);

    bool key_LEFT = false;
    bool key_RIGHT = false;

    while (PBState->run == LEVEL3) {
        while (SDL_PollEvent(&PBState->event)) {
            if (PBState->event.type == SDL_QUIT) {
                PBState->run = QUIT;
            }
            else if (PBState->event.type == SDL_KEYDOWN) {
                switch (PBState->event.key.keysym.sym) {
                case SDLK_a:
                    key_LEFT = true;
                    break;
                case SDLK_d:
                    key_RIGHT = true;
                    break;
                case SDLK_MINUS:
                    if (volume > 0) {
                        volume -= MAX_VOLUME / 10;
                    }
                    else {
                        volume = 0;
                    }
                    break;
                case SDLK_EQUALS:
                    if (volume < MAX_VOLUME) {
                        volume += MAX_VOLUME / 10;
                    }
                    else {
                        volume = MAX_VOLUME;
                    }
                case SDLK_ESCAPE:
                    PBState->run = MENU;
                    break;
                }
                Mix_Volume(-1, volume);
                Mix_VolumeMusic(volume);
            }

            else if (PBState->event.type == SDL_KEYUP) {
                switch (PBState->event.key.keysym.sym) {
                case SDLK_a:
                    key_LEFT = false;
                    break;

                case SDLK_d:
                    key_RIGHT = false;
                    break;
                }
            }
        }
        if(plane->PlaneRect.x >= WINDOW_WIDTH && SDL_GetTicks() % 120 == 0) {
            SpawnCat(catManager, PBState->renderer, true);
        }
        if (SDL_GetTicks() % 100 == 0) {
            SpawnCat(catManager, PBState->renderer, false);
        }
    
        CounterSprites(counter);
        if (key_LEFT) {
            player->playerRect.x -= player->mVelX;
        }
        if (key_RIGHT) {
            player->playerRect.x += player->mVelX;
        }
        if (player->playerRect.x <= 0) {
            player->playerRect.x += player->mVelX;
        }
        if (player->playerRect.x >= WINDOW_WIDTH - LVL3PLAYER_WIDTH) {
            player->playerRect.x = WINDOW_WIDTH - LVL3PLAYER_WIDTH;
        }

        if(SDL_GetTicks()%5 == 0) {
            ++bcat;
        }
        if(bcat/3 >= CATS_FRAMES) {
            bcat = 0;
        }
        if (SDL_GetTicks() % 3 == 0) {
            ++backgr;
        }
        if (backgr >= BACKGROUNDS) {
            backgr = 0;
        }
        if(counter->countnumber == 35) {
            PBState->run = MENU;
        }
        SDL_RenderClear(PBState->renderer);
        catManager_update(catManager, player, counter);
        Plane_move(plane);
        Player_animate(player);
        SDL_RenderCopy(PBState->renderer, gMap[backgr], NULL, &g_map);

        Player_show(player, PBState->renderer);
        CatArr_show(catManager, PBState->renderer, bcat);
        Counter_show(counter, PBState->renderer);
        Plane_show(plane, PBState->renderer);
        SDL_RenderPresent(PBState->renderer);

        if (counter->countHP == 3) {
            PBState->run = GAME_OVER;
            PBState->rerun = LEVEL3;
        }

        SDL_Delay(1000 / 60);
    }
    Player_destroy(player);
    Counter_destroy(counter);
    CatManager_destroy(catManager);
    Plane_destroy(plane);

    for(int i = 0; i < BACKGROUNDS; i++)
    {
        SDL_DestroyTexture(gMap[i]);
    }
    Mix_FreeMusic(gBGMusic);
}


