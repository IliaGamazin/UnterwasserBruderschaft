#include "header.h"

int countnumber = 0;
int countHP = 0;

typedef struct
{
    int mVelX;
    SDL_Rect playerRect;
    SDL_Rect playerClip[PLAYER_FRAMES];

    SDL_Texture* PlayerTextureIdle;

} PlayerSecretLvL;

typedef struct
{
    int cVelX;
    int cVelY;
    SDL_Rect catsRect;
    SDL_Rect catsClip[CATS_FRAMES];
    SDL_Texture* FallingCat;
    SDL_Texture* BubbleCat;
    SDL_Texture* CurrentTex;

    Mix_Chunk* CatFell;
} FallingCats;

typedef struct 
{
    FallingCats** cats;
    int quantity;
    int count;
    int* catPosArr;
    Mix_Chunk* CatSpawn;
    Mix_Chunk* CatMeow;
} CatManager;

typedef struct
{
    SDL_Rect UnitsRect;
    SDL_Rect TensRect;

    SDL_Rect UnitsClip;
    SDL_Rect TensClip;

    SDL_Texture* UnitsTexture;
    SDL_Texture* TensTexture;

}Counter;

typedef struct
{
    SDL_Rect HPcounterRect;
    SDL_Rect HPcounterClip;
    SDL_Texture* HPCounterTexture;

}HPCounter;

typedef struct
{
    int pVelX;
    SDL_Rect PlaneRect;
    SDL_Rect PlaneClip[PLAYER_FRAMES];
    SDL_Texture* Plane;

    Mix_Chunk* PlaneSound;
}Enemy;

typedef struct
{
    int bVelX;
    SDL_Rect StoneRect;
    SDL_Texture* StoneTexture;
    Mix_Chunk* StoneColl;
}Stone;

typedef struct
{
    int capacity;
    int count;
    int* StonesPosArr;
    Stone** stones;

    Mix_Chunk* StoneSpawn;

}StoneManager;

PlayerSecretLvL* Player_create(SDL_Renderer* gRenderer)
{
    PlayerSecretLvL* player = (PlayerSecretLvL*)malloc(sizeof(PlayerSecretLvL));

        player->playerRect.x = 500;
        player->playerRect.y = 550;
        player->mVelX = PLAYER_VEL;
        player->playerRect.w = PLAYER_WIDTH;
        player->playerRect.h = PLAYER_HEIGHT;
        player->PlayerTextureIdle = IMG_LoadTexture(gRenderer, "images/lodkadone.png");

        return player;
}

FallingCats* Cat_create(SDL_Renderer* gRenderer, int x) 
{
    FallingCats* cat = (FallingCats*)malloc(sizeof(FallingCats));
    cat->catsRect.x = x;
    cat->catsRect.y = -CATS_SIZE;
    cat->catsRect.w = CATS_SIZE;
    cat->catsRect.h = CATS_SIZE;
    cat->cVelX = 0;
    cat->cVelY = 3;

    for(int i = 0; i < CATS_FRAMES; i++)
     {
        cat->catsClip[i].x = 70*i;
        cat->catsClip[i].y = 0;
        cat->catsClip[i].w = 70;
        cat->catsClip[i].h = 50;
     }

    cat->FallingCat = IMG_LoadTexture(gRenderer, "images/kotuni.png");
    cat->BubbleCat = IMG_LoadTexture(gRenderer, "images/kotp.png");
    cat-> CurrentTex = cat-> FallingCat;

    cat->CatFell = Mix_LoadWAV("sound_SL/cat_die.wav");
    return cat;
}

CatManager* CatManager_create(int quantity) {
    CatManager* catManager = (CatManager*)malloc(sizeof(CatManager));

    catManager->cats = (FallingCats**)malloc(quantity * sizeof(FallingCats*));
    catManager->catPosArr = (int*)malloc(CATS_POS_COUNT * sizeof(int));
    catManager->catPosArr[0] = 65;
    for (int i = 1; i < CATS_POS_COUNT; i++)
    {
        catManager->catPosArr[i] = catManager->catPosArr[i - 1]+ 110;
    }
    catManager->quantity = quantity;
    catManager->count = 0;
    catManager->CatSpawn = Mix_LoadWAV("sound_SL/cat_spawn.wav");
    catManager->CatMeow = Mix_LoadWAV("sound_SL/cat_meow.wav");

    return catManager;
}

Enemy* Plane_create(SDL_Renderer* gRenderer)
{
    Enemy* plane = (Enemy*)malloc(sizeof(Enemy));

    plane->PlaneRect.x = -200;
    plane->PlaneRect.y = 150;
    plane->PlaneRect.w = PLANE_WIDTH;
    plane->PlaneRect.h = PLANE_HEIGHT;
    plane->pVelX = PLANE_VEL;

    plane->Plane = IMG_LoadTexture(gRenderer, "images/samolet.png");
    plane->PlaneSound = Mix_LoadWAV("sound_SL/plane.wav");

    return plane;
}

Stone* Stone_create(SDL_Renderer* gRenderer, int x)
{
    Stone* stone = (Stone*)malloc(sizeof(Stone));

    stone->StoneRect.x = x;
    stone->StoneRect.y = -STONE_SIZE;
    stone->StoneRect.w = STONE_SIZE;
    stone->StoneRect.h = STONE_SIZE;

    stone->bVelX = STONE_VEL;
    stone->StoneTexture = IMG_LoadTexture(gRenderer, "images/bull.png");

    stone->StoneColl = Mix_LoadWAV("sound_SL/bam.wav");

    return stone;
}

StoneManager* StoneManager_create(int capacity)
{
    StoneManager* stoneManager = (StoneManager*)malloc(sizeof(StoneManager));

    stoneManager->stones = (Stone**)malloc(capacity * sizeof(Stone*));

    stoneManager->StonesPosArr = (int*)malloc(STONES_POS_COUNT * sizeof(int));

    stoneManager->StonesPosArr[0] = 80;
    for (int i = 1; i < STONES_POS_COUNT; i++)
    {
        stoneManager->StonesPosArr[i] = stoneManager->StonesPosArr[i - 1] + 150;
    }

    stoneManager->capacity = capacity;
    stoneManager->count = 0;

    stoneManager->StoneSpawn = Mix_LoadWAV("sound_SL/bullspawn.wav");

    return stoneManager;
}

void SpawnCat(CatManager* catManager, SDL_Renderer* gRenderer)
{
        if (catManager->count < catManager->quantity)
        {
            FallingCats* newCat = Cat_create(gRenderer, catManager->catPosArr[rand() % 12]);
            catManager->cats[catManager->count++] = newCat;
            Mix_PlayChannel(-1, catManager->CatSpawn, 0);
        }
}

void SpawnStone(StoneManager* stoneManager, SDL_Renderer* gRenderer)
{
    if (stoneManager->count < stoneManager->capacity)
    {
        Stone* newStone = Stone_create(gRenderer, stoneManager->StonesPosArr[rand()%8]);
        stoneManager->stones[stoneManager->count++] = newStone;

        Mix_PlayChannel(0, stoneManager->StoneSpawn, 0);
    }
}

Counter* Counter_create(SDL_Renderer* gRenderer)
{
    Counter* counter = (Counter*)malloc(sizeof(Counter));

    counter->TensRect.x = 0;
    counter->TensRect.y = 0;
    counter->UnitsRect.x = 50;
    counter->UnitsRect.y = 0;

    counter->TensRect.w = COUNTER_SIZE;
    counter->TensRect.h = COUNTER_SIZE;
    counter->UnitsRect.w = COUNTER_SIZE;
    counter->UnitsRect.h = COUNTER_SIZE;

    counter->TensClip.x = 0;
    counter->TensClip.y = 0;
    counter->TensClip.w = 32;
    counter->TensClip.h = 40;

    counter->UnitsClip.x = 0;
    counter->UnitsClip.y = 0;
    counter->UnitsClip.w = 32;
    counter->UnitsClip.h = 40;

    counter->TensTexture = IMG_LoadTexture(gRenderer, "images/n1.png");
    counter->UnitsTexture = IMG_LoadTexture(gRenderer, "images/n2.png");

    return counter;
}

HPCounter* HPcounter_create(SDL_Renderer* gRenderer)
{
    HPCounter* hp = (HPCounter*)malloc(sizeof(HPCounter));

    hp->HPcounterRect.x = 0;
    hp->HPcounterRect.y = 70;
    hp->HPcounterRect.w = HPCOUNTER_WIDTH;
    hp->HPcounterRect.h = HPCOUNTER_HEIGHT;

    hp->HPcounterClip.x = 0;
    hp->HPcounterClip.y = 0;
    hp->HPcounterClip.w = HPCOUNTER_WIDTH;
    hp->HPcounterClip.h = HPCOUNTER_HEIGHT;

    hp->HPCounterTexture = IMG_LoadTexture(gRenderer, "images/catbread2.png");

    return hp;
}
int checkCollission(SDL_Rect a, SDL_Rect b) {

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if (bottomA <= topB)
    {
        return 0;
    }

    if (topA >= bottomB)
    {
        return 0;
    }

    if (rightA <= leftB)
    {
        return 0;
    }

    if (leftA >= rightB)
    {
        return 0;
    }
    return 1;
}

void Cat_move(FallingCats* cat, PlayerSecretLvL* player, CatManager* catManager, SDL_Renderer* gRenderer)
{

    cat->catsRect.y += cat->cVelY;
    cat->catsRect.x += cat->cVelX;
     
       if ((cat->catsRect.y + CATS_SIZE > 650))
    {
        cat->catsRect.y -= cat->cVelY;
        cat-> CurrentTex = cat->BubbleCat;
        //SDL_DestroyTexture(cat->FallingCat);
        Mix_PlayChannel(-1, cat->CatFell, 0);

        if (cat->catsRect.x < SCREEN_WIDTH / 2) 
        {
            cat->cVelX -= 2;
            cat->cVelY *= -1;
        }
        else
        {
            cat->cVelX += 2;
            cat->cVelY *= -1;
        }
    }
          if (checkCollission(cat->catsRect, player->playerRect)) 
          {

                  Mix_PlayChannel(0, catManager->CatMeow, 0);
                  cat->catsRect.y = -100;
                  cat->catsRect.x = catManager->catPosArr[rand() % 12];
                  countnumber++;
          }
    }


void Stone_move(Stone* stone, PlayerSecretLvL* player, StoneManager* stoneManager)
{

        stone->StoneRect.y += STONE_VEL;

    if (checkCollission(stone->StoneRect, player->playerRect))
    {
        stone->StoneRect.y = -50;
        stone->StoneRect.x = stoneManager->StonesPosArr[rand() % 8];

        Mix_PlayChannel(2, stone->StoneColl, 0);

        countHP++;
    }
}

void Plane_destroy(Enemy* plane)
{
    SDL_DestroyTexture(plane->Plane);
    free(plane);
}

void Stone_destroy(Stone* stone)
{
    Mix_FreeChunk(stone->StoneColl);
    SDL_DestroyTexture(stone->StoneTexture);
    free(stone);
}

void StoneManager_destroy(StoneManager* stoneManager)
{
    for (int i = 0; i < stoneManager->count; ++i) {
        Stone_destroy(stoneManager->stones[i]);
    }
    free(stoneManager->stones);
    free(stoneManager);
}

void destroy_CollidedStone(StoneManager* stoneManager, int index)
{
    Stone_destroy(stoneManager->stones[index]);
    if (index < stoneManager->count - 1) {
        stoneManager->stones[index] = stoneManager->stones[stoneManager->count - 1];
    }
    --stoneManager->count;
}

void stoneManager_update(StoneManager* stoneManager, PlayerSecretLvL* player)
{
    for (int i = 0; i < stoneManager->count; i++)
    {
        Stone_move(stoneManager->stones[i], player, stoneManager);

        if (stoneManager->stones[i]->StoneRect.y >= 650)
        {
            destroy_CollidedStone(stoneManager, i);
            --i;
        }
    }
}

void Plane_move(Enemy* plane)
{
    for(int i = 0; i<PLAYER_FRAMES; i++)
    {
        plane->PlaneClip[i].x = 0;
        plane->PlaneClip[i].y = 0;
        plane->PlaneClip[i].w = 169;
        plane->PlaneClip[i].h = 56;
    }

    plane->PlaneRect.x += plane->pVelX;

    if (plane->PlaneRect.x <= SCREEN_WIDTH)
    {
        Mix_PlayChannel(-1, plane->PlaneSound, 0);
    }
    if (plane->PlaneRect.x >= SCREEN_WIDTH + PLANE_WIDTH)
    {
        plane->PlaneRect.x = -200;
    }
}

void Cats_destroy(FallingCats* cat)
{
    //SDL_DestroyTexture(cat->FallingCat);
    SDL_DestroyTexture(cat-> CurrentTex);
    SDL_DestroyTexture(cat->BubbleCat);
    Mix_FreeChunk(cat->CatFell);
    free(cat);
}
void destroy_CollidedCat(CatManager* catManager, int index)
{
    Cats_destroy(catManager->cats[index]);

    if (index < catManager->count - 1)
    {
        catManager->cats[index] = catManager->cats[catManager->count - 1];
    }
    --catManager->count;
}

void catManager_update(CatManager* catManager, PlayerSecretLvL* player, SDL_Renderer* gRenderer)
{
    for (int i = 0; i < catManager->count; i++)
    {
        Cat_move(catManager->cats[i], player, catManager, gRenderer);

        if (catManager->cats[i]->catsRect.x <= 0 || catManager->cats[i]->catsRect.x >= SCREEN_WIDTH)
        {
            destroy_CollidedCat(catManager, i);
            --i;
        }
    }
}

void PlayerSprites(PlayerSecretLvL* player)
{
    for(int i = 0; i< PLAYER_FRAMES; i++)
    {
    player->playerClip[i].x = 128*i;
    player->playerClip[i].y = 0;
    player->playerClip[i].w = 100;
    player->playerClip[i].h = 87;
    }
}

void CounterSprites(Counter* counter, int countnumber)
{
   switch (countnumber)
    {
    case 1:
        counter->UnitsClip.x = 32;
        break;
    case 2:
        counter->UnitsClip.x = 32*2;
        break;
    case 3:
        counter->UnitsClip.x = 32*3;
        break;
    case 4:
        counter->UnitsClip.x = 32 * 4;
        break;
    case 5:
        counter->UnitsClip.x = 32 * 5;
        break;
    case 6:
        counter->UnitsClip.x = 32 * 6;
        break;
    case 7:
        counter->UnitsClip.x = 32 * 7;
        break;
    case 8:
        counter->UnitsClip.x = 32 * 8;
        break;
    case 9:
        counter->UnitsClip.x = 32 * 9;
        break;
    case 10:
        counter->UnitsClip.x = 0;
        counter->TensClip.x = 32;
        break;
    case 11:
        counter->UnitsClip.x = 32;
        break;
    case 12:
        counter->UnitsClip.x = 32 * 2;
        break;
    case 13:
        counter->UnitsClip.x = 32 * 3;
        break;
    case 14:
        counter->UnitsClip.x = 32 * 4;
        break;
    case 15:
        counter->UnitsClip.x = 32 * 5;
        break;
    case 16:
        counter->UnitsClip.x = 32 * 6;
        break;
    case 17:
        counter->UnitsClip.x = 32 * 7;
        break;
    case 18:
        counter->UnitsClip.x = 32 * 8;
        break;
    case 19:
        counter->UnitsClip.x = 32 * 9;
        break;
    case 20:
        counter->UnitsClip.x = 0;
        counter->TensClip.x = 32*2;
    }
}

void HPcounterSprites(HPCounter* hp, int countHP)
{
    switch ((countHP))
    {
    case 1:
        hp->HPcounterClip.w = HPCOUNTER_WIDTH - 40;
        hp->HPcounterRect.w = HPCOUNTER_WIDTH - 40;
        break;
    case 2:
        hp->HPcounterClip.w = HPCOUNTER_WIDTH - 80;
        hp->HPcounterRect.w = HPCOUNTER_WIDTH - 80;
        break;
    case 3:
        SDL_DestroyTexture(hp->HPCounterTexture);
    }
}
void Player_destroy(PlayerSecretLvL* player)
{
    SDL_DestroyTexture(player->PlayerTextureIdle);
    free(player);
}

void CatManager_destroy(CatManager* catManager)
{
    for (int i = 0; i < catManager->count; i++) {
        Cats_destroy(catManager->cats[i]);
    }
    Mix_FreeChunk(catManager->CatSpawn);
    Mix_FreeChunk(catManager->CatMeow);
    free(catManager->cats);
    free(catManager);
}

void Counter_destroy(Counter* counter)
{
    SDL_DestroyTexture(counter->UnitsTexture);
    SDL_DestroyTexture(counter->TensTexture);
    free(counter);
}

void HPcounter_destroy(HPCounter* hp)
{
    SDL_DestroyTexture(hp->HPCounterTexture);
    free(hp);
}

void Player_show(PlayerSecretLvL* player, SDL_Renderer* gRenderer, bool directionLeft, bool directionRight, int frame)
{
   SDL_Rect* CurrentClip = &player->playerClip[frame / 4] ;
        SDL_RenderCopy(gRenderer, player->PlayerTextureIdle,CurrentClip, &player->playerRect);
}

void Cat_show(FallingCats* cat, SDL_Renderer* gRenderer, int bcat) 
{
    if(cat-> CurrentTex == cat-> FallingCat)
    {
        SDL_RenderCopy(gRenderer, cat->FallingCat, NULL, &cat->catsRect);
    }
    else
    {
        SDL_Rect* CurrentClip = &cat->catsClip[bcat / 3] ;
        SDL_RenderCopy(gRenderer, cat->BubbleCat, CurrentClip, &cat->catsRect);
    }
    //SDL_RenderCopy(gRenderer, cat->CurrentTex, &cat->catsRect);
    //SDL_RenderCopy(gRenderer, cat->BubbleCat, NULL, &cat->catsRect);
}

void Stone_show(Stone* stone, SDL_Renderer* gRenderer) {
    SDL_RenderCopy(gRenderer, stone->StoneTexture, NULL, &stone->StoneRect);
}

void CatArr_show(CatManager* catManager, SDL_Renderer* gRenderer, int bcat)
{
    for (int i = 0; i < catManager->count; i++)
    {
        Cat_show(catManager->cats[i], gRenderer, bcat);
    }
}

void StoneArr_show(StoneManager* stoneManager, SDL_Renderer* gRenderer)
{
    for (int i = 0; i < stoneManager->count; i++)
    {
        Stone_show(stoneManager->stones[i], gRenderer);
    }
}

void Counter_show(Counter* counter, SDL_Renderer* gRenderer)
{
    SDL_RenderCopy(gRenderer, counter->UnitsTexture, &counter->UnitsClip, &counter->UnitsRect);
    SDL_RenderCopy(gRenderer, counter->TensTexture, &counter->TensClip, &counter->TensRect);
}

void Plane_show(Enemy* plane, SDL_Renderer* gRenderer, int frame)
{
    SDL_Rect* CurrentClip = &plane->PlaneClip[frame/4];
    SDL_RenderCopy(gRenderer, plane->Plane, CurrentClip, &plane->PlaneRect);
}


void showAllStones(SDL_Renderer* gRenderer, StoneManager* stoneManager) {

    for (int i = 0; i < stoneManager->count; ++i) {
        Stone_show(stoneManager->stones[i], gRenderer);
    }
}

void HPcounter_show(HPCounter* hp, SDL_Renderer* gRenderer)
{
    SDL_RenderCopy(gRenderer, hp->HPCounterTexture, &hp->HPcounterClip, &hp->HPcounterRect);
}

void destroy_level(SDL_Window* gWindow, SDL_Renderer* gRenderer, PlayerSecretLvL* player, Counter* counter, CatManager* catManager, HPCounter* hp, Enemy* plane, StoneManager* stoneManager)
{
    Player_destroy(player);
    Counter_destroy(counter);
    CatManager_destroy(catManager);
    HPcounter_destroy(hp);
    Plane_destroy(plane);
    StoneManager_destroy(stoneManager);

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
}

int main(int argc, char* args[])
 
{
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
    HPCounter* hp = HPcounter_create(gRenderer);
    CatManager* catManager = CatManager_create(5);
    StoneManager* stoneManager = StoneManager_create(8);

    bool key_LEFT = false;
    bool key_RIGHT = false;
    PlayerSprites(player);

    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    key_LEFT = true;
                    break;

                case SDLK_RIGHT:
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
                case SDLK_LEFT:
                    key_LEFT = false;
                    break;

                case SDLK_RIGHT:
                    key_RIGHT = false;
                    break;
                }
            }
        }

        if (SDL_GetTicks() % 100 == 0)
        {
            SpawnCat(catManager, gRenderer);
        }

        if ((SDL_GetTicks() >= 6000 && SDL_GetTicks() <= 11000))
        {
            Plane_move(plane);
            bulmove = true;
        }
        if (bulmove == true)
        {
            if (SDL_GetTicks() % 90 == 0)
            {
                SpawnStone(stoneManager, gRenderer);
            }
        }

        CounterSprites(counter, countnumber);
        HPcounterSprites(hp, countHP);

        if (key_LEFT) {
            player->playerRect.x -= player->mVelX;
        }
        if (key_RIGHT) {
            player->playerRect.x += player->mVelX;
        }
        if (player->playerRect.x <= 0)
        {
            player->playerRect.x += player->mVelX;
        }
        if (player->playerRect.x >= SCREEN_WIDTH - PLAYER_WIDTH)
        {
            player->playerRect.x = SCREEN_WIDTH - PLAYER_WIDTH;
        }

        if (SDL_GetTicks() % 3 == 0)
        {
            ++frame;
        }

        if (frame/4 >= PLAYER_FRAMES)
        {
            frame = 0;
        }

        if(SDL_GetTicks()%5==0)
        {
            ++bcat;
        }

        if(bcat/3 >= CATS_FRAMES)
        {
            bcat = 0;
        }
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);


        // int frame = SDL_GetTicks() / 10 % (4); 

        catManager_update(catManager, player, gRenderer);
        stoneManager_update(stoneManager, player);
        
        SDL_RenderCopy(gRenderer, gMap[backgr], NULL, &g_map);

        if (SDL_GetTicks() % 3 == 0)
        {
            ++backgr;
        }
        if (backgr >= BACKGROUNDS)
        {
        backgr = 0;
        }

        Player_show(player, gRenderer, key_LEFT, key_RIGHT, frame);
        Counter_show(counter, gRenderer);

        HPcounter_show(hp, gRenderer);

        CatArr_show(catManager, gRenderer, bcat);
        Plane_show(plane, gRenderer, frame);
        StoneArr_show(stoneManager, gRenderer);
        SDL_RenderPresent(gRenderer);

        SDL_Delay(1000 / 60);
    }
    destroy_level(gWindow, gRenderer, player, counter, catManager, hp, plane, stoneManager);

    for(int i = 0; i< BACKGROUNDS; i++)
    {
        SDL_DestroyTexture(gMap[i]);
    }
    Mix_FreeMusic(gBGMusic);
    return 0;
}
