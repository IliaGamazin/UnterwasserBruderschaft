#include "../inc/header.h"

int main(void) {
    SDL_Init(SDL_INIT_VIDEO);
    Mix_Init(MIX_INIT_MP3);
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    SDL_Event event;
    SDL_Window* gWindow = SDL_CreateWindow("SecretLevel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_TARGETTEXTURE);
    Mix_Music* gBGMusic = Mix_LoadMUS("sound/bgm.wav");

    SDL_Texture* gMap[BACKGROUNDS];
    SDL_Rect g_map;

    gMap[0] = IMG_LoadTexture(gRenderer, "images/fon1.png");
    gMap[1] = IMG_LoadTexture(gRenderer, "images/fon2.png");
    gMap[2] = IMG_LoadTexture(gRenderer, "images/fon3.png");
    gMap[3] = IMG_LoadTexture(gRenderer, "images/fon4.png");
    gMap[4] = IMG_LoadTexture(gRenderer, "images/fon5.png");
    gMap[5] = IMG_LoadTexture(gRenderer, "images/fon6.png");
    gMap[6] = IMG_LoadTexture(gRenderer, "images/fon7.png");

    int volume = MAX_VOLUME / 2;

    Mix_PlayMusic(gBGMusic, -1);

    g_map.w = SCREEN_WIDTH;
    g_map.h = SCREEN_HEIGHT;
    g_map.x = 0;
    g_map.y = 0;

    bool quit = false;
    bool bulmove = false;
    int frame = 0;
    int backgr = 0;
    int bcat = 0;

    PlayerSecretLvL* player = Player_create(gRenderer);
    Enemy* plane = Plane_create(gRenderer);
    Counter* counter = Counter_create(gRenderer);
    CatManager* catManager = CatManager_create(5);
    StoneManager* stoneManager = StoneManager_create(8);

    bool key_LEFT = false;
    bool key_RIGHT = false;
    PlayerSprites(player);

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_a:
                    key_LEFT = true;
                    break;

                case SDLK_d:
                    key_RIGHT = true;
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

                case SDLK_EQUALS:
                    printf("\n Volume: %d", volume);
                    if (volume < MAX_VOLUME) {
                        volume += MAX_VOLUME / 10;
                    }
                    else {
                        volume = MAX_VOLUME;
                    }
                }
                Mix_Volume(-1, volume);
                Mix_VolumeMusic(volume);
            }

            else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                case SDLK_a:
                    key_LEFT = false;
                    break;

                case SDLK_d:
                    key_RIGHT = false;
                    break;
                }
            }
        }
        if (SDL_GetTicks() % 100 == 0) {
            SpawnCat(catManager, gRenderer);
        }
        if ((SDL_GetTicks() >= 6000 && SDL_GetTicks() <= 13000)){
            Plane_move(plane);
            bulmove = true;
        }
        if (bulmove == true) {
            if (SDL_GetTicks() % 90 == 0) {
                SpawnStone(stoneManager, gRenderer);
            }
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
        if (player->playerRect.x >= SCREEN_WIDTH - PLAYER_WIDTH) {
            player->playerRect.x = SCREEN_WIDTH - PLAYER_WIDTH;
        }
        if (SDL_GetTicks() % 3 == 0) {
            ++frame;
        }
        if (frame/4 >= PLAYER_FRAMES) {
            frame = 0;
        }
        if(SDL_GetTicks()%5==0) {
            ++bcat;
        }
        if(bcat/3 >= CATS_FRAMES) {
            bcat = 0;
        }

        catManager_update(catManager, player, counter);
        stoneManager_update(stoneManager, player, counter);
        SDL_RenderCopy(gRenderer, gMap[backgr], NULL, &g_map);

        if (SDL_GetTicks() % 3 == 0) {
            ++backgr;
        }
        if (backgr >= BACKGROUNDS) {
        backgr = 0;
        }

        Player_show(player, gRenderer, frame);
        Counter_show(counter, gRenderer);
        CatArr_show(catManager, gRenderer, bcat);
        Plane_show(plane, gRenderer, frame);
        StoneArr_show(stoneManager, gRenderer);
        SDL_RenderPresent(gRenderer);

        SDL_Delay(1000 / 60);
    }
    Player_destroy(player);
    Counter_destroy(counter);
    CatManager_destroy(catManager);
    Plane_destroy(plane);
    StoneManager_destroy(stoneManager);

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    IMG_Quit();
    SDL_Quit();
    Mix_Quit();

    for(int i = 0; i< BACKGROUNDS; i++)
    {
        SDL_DestroyTexture(gMap[i]);
    }
    Mix_FreeMusic(gBGMusic);
    return 0;
}


