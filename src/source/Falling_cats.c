#include "../inc/header.h"

FallingCats *Cat_create(SDL_Renderer* gRenderer, int x) {
    FallingCats *cat = (FallingCats*)malloc(sizeof(FallingCats));
    cat->catsRect.x = x;
    cat->catsRect.y = -CATS_SIZE;
    cat->catsRect.w = CATS_SIZE;
    cat->catsRect.h = CATS_SIZE;
    cat->cVelX = 0;
    cat->cVelY = 3;

    for(int i = 0; i < CATS_FRAMES; i++) {
        cat->catsClip[i].x = 70*i;
        cat->catsClip[i].y = 0;
        cat->catsClip[i].w = 70;
        cat->catsClip[i].h = 50;
     }

    cat->FallingCat = IMG_LoadTexture(gRenderer, "images/kotuni.png");
    cat->BubbleCat = IMG_LoadTexture(gRenderer, "images/kotp.png");
    cat-> CurrentTex = cat-> FallingCat;

    cat->CatFell = Mix_LoadWAV("sound/cat_die.wav");
    return cat;
}

CatManager *CatManager_create(int quantity) {
    CatManager *catManager = (CatManager*)malloc(sizeof(CatManager));

    catManager->cats = (FallingCats**)malloc(quantity * sizeof(FallingCats*));
    catManager->catPosArr = (int*)malloc(CATS_POS_COUNT * sizeof(int));
    catManager->catPosArr[0] = 65;
    for (int i = 1; i < CATS_POS_COUNT; i++) {
        catManager->catPosArr[i] = catManager->catPosArr[i - 1]+ 110;
    }
    catManager->quantity = quantity;
    catManager->count = 0;
    catManager->CatSpawn = Mix_LoadWAV("sound/cat_spawn.wav");
    catManager->CatMeow = Mix_LoadWAV("sound/cat_meow.wav");

    return catManager;
}
void SpawnCat(CatManager *catManager, SDL_Renderer* gRenderer) {
        if (catManager->count < catManager->quantity) {
            FallingCats* newCat = Cat_create(gRenderer, catManager->catPosArr[rand() % 12]);
            catManager->cats[catManager->count++] = newCat;
            Mix_PlayChannel(-1, catManager->CatSpawn, 0);
        }
}
void Cat_move(FallingCats *cat, PlayerSecretLvL *player, CatManager *catManager, Counter *counter) {

    cat->catsRect.y += cat->cVelY;
    cat->catsRect.x += cat->cVelX;
     
       if ((cat->catsRect.y + CATS_SIZE > 650)) {
        cat->catsRect.y -= cat->cVelY;
        cat-> CurrentTex = cat->BubbleCat;
        Mix_PlayChannel(-1, cat->CatFell, 0);

        if (cat->catsRect.x < SCREEN_WIDTH / 2) {
            cat->cVelX -= 2;
            cat->cVelY *= -1;
        }
        else {
            cat->cVelX += 2;
            cat->cVelY *= -1;
        }
    }
          if (checkCollission(cat->catsRect, player->playerRect)) {
                  Mix_PlayChannel(0, catManager->CatMeow, 0);
                  cat->catsRect.y = -100;
                  cat->catsRect.x = catManager->catPosArr[rand() % 12];
                  counter->countnumber++;
          }
    }

void CatsSprites(FallingCats* cat) {
     for(int i = 0; i < CATS_FRAMES; i++)
     {
        cat->catsClip[i].x = 70*i;
        cat->catsClip[i].y = 0;
        cat->catsClip[i].w = 80;
        cat->catsClip[i].h = 60;
     }
}
void Cats_destroy(FallingCats *cat) {
    SDL_DestroyTexture(cat-> CurrentTex);
    SDL_DestroyTexture(cat->BubbleCat);
    Mix_FreeChunk(cat->CatFell);
    free(cat);
}
void destroy_CollidedCat(CatManager *catManager, int index) {
    Cats_destroy(catManager->cats[index]);

    if (index < catManager->count - 1) {
        catManager->cats[index] = catManager->cats[catManager->count - 1];
    }
    --catManager->count;
}

void catManager_update(CatManager *catManager, PlayerSecretLvL *player, Counter *counter) {
    for (int i = 0; i < catManager->count; i++) {
        Cat_move(catManager->cats[i], player, catManager,counter);

        if (catManager->cats[i]->catsRect.x <= 0 || catManager->cats[i]->catsRect.x >= SCREEN_WIDTH) {
            destroy_CollidedCat(catManager, i);
            --i;
        }
    }
}
void CatManager_destroy(CatManager *catManager) {
    for (int i = 0; i < catManager->count; i++) {
        Cats_destroy(catManager->cats[i]);
    }
    Mix_FreeChunk(catManager->CatSpawn);
    Mix_FreeChunk(catManager->CatMeow);
    free(catManager->cats);
    free(catManager);
}
void Cat_show(FallingCats *cat, SDL_Renderer* gRenderer, int bcat) {
    if(cat-> CurrentTex == cat-> FallingCat) {
        SDL_RenderCopy(gRenderer, cat->FallingCat, NULL, &cat->catsRect);
    }
    else {
        SDL_Rect* CurrentClip = &cat->catsClip[bcat / 3] ;
        SDL_RenderCopy(gRenderer, cat->BubbleCat, CurrentClip, &cat->catsRect);
    }
}
void CatArr_show(CatManager *catManager, SDL_Renderer* gRenderer, int bcat) {
    for (int i = 0; i < catManager->count; i++) {
        Cat_show(catManager->cats[i], gRenderer, bcat);
    }
}
