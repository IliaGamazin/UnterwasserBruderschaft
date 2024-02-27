#include "../inc/FallingCats.h"
#include "../inc/PlayerLvl3.h"
#include "../inc/Counter.h"

CatManager *CatManager_create(int quantity) {
    CatManager *catManager = (CatManager*)malloc(sizeof(CatManager));

    catManager->cats = (FallingCat**)malloc(quantity * sizeof(FallingCat*));
    catManager->CatPosArr = (int*)malloc(CATS_POS_COUNT * sizeof(int));
    catManager->CatPosArr[0] = 65;

    for (int i = 1; i < CATS_POS_COUNT; i++) {
        catManager->CatPosArr[i] = catManager->CatPosArr[i - 1]+ 110;
    }

    catManager->StonesPosArr = (int*)malloc(STONES_POS_COUNT * sizeof(int));
    catManager->StonesPosArr[0] = 80;

    for (int i = 1; i < STONES_POS_COUNT; i++) {
        catManager->StonesPosArr[i] = catManager->StonesPosArr[i - 1] + 150;    
    }

    catManager->quantity = quantity;
    catManager->count = 0;
    catManager->CatSpawn = Mix_LoadWAV("resource/sound/cat_spawn.wav");
    catManager->CatMeow = Mix_LoadWAV("resource/sound/cat_meow.wav");
    catManager->StoneSpawn = Mix_LoadWAV("resource/sound/bullspawn.wav");
    catManager->StoneColl = Mix_LoadWAV("resource/sound/bam.wav");

    return catManager;
}
FallingCat *Falling_cat_new(int x, bool is_stone, SDL_Renderer *gRenderer) {
    FallingCat *cat = malloc(sizeof(FallingCat));
    cat->catsRect.x = x;
    cat->catsRect.y = -CATS_SIZE;
    cat->catsRect.w = CATS_SIZE;
    cat->catsRect.h = CATS_SIZE;
    cat->cVelX = 0;
    cat->is_bubble = false;
    cat->is_stone = is_stone;
    if(is_stone) {
        cat->cVelY = 5;
        cat->FallingCat = IMG_LoadTexture(gRenderer, "resource/img/level3/stone.png");
        cat->BubbleCat = IMG_LoadTexture(gRenderer, "resource/img/level3/stone.png");
        cat->CatFell = Mix_LoadWAV("resource/sound/plop.wav");
    }
    else {
        cat->cVelY = 3;
        cat->FallingCat = IMG_LoadTexture(gRenderer, "resource/img/level3/kotuni.png");
        cat->BubbleCat = IMG_LoadTexture(gRenderer, "resource/img/level3/kotp.png");
        cat->CatFell = Mix_LoadWAV("resource/sound/plop.wav");
    }
    for(int i = 0; i < CATS_FRAMES; i++) {
        cat->catsClip[i].x = 80 * i;
        cat->catsClip[i].y = 0;
        cat->catsClip[i].w = 53;
        cat->catsClip[i].h = 50;
    }
    return cat;
}
void SpawnCat(CatManager *catManager, SDL_Renderer* gRenderer, bool is_stone) {
    if (catManager->count < catManager->quantity) {
        catManager->cats[catManager->count++] = Falling_cat_new(catManager->CatPosArr[rand() % 12], is_stone, gRenderer);
        if(is_stone) {
            Mix_PlayChannel(-1, catManager->StoneSpawn, 0);
        }
        else {
            Mix_PlayChannel(-1, catManager->CatSpawn, 0);
        }
    }
}
void Cat_move(FallingCat *cat, PlayerSecretLvL *player, CatManager *catManager, Counter *counter) {

    cat->catsRect.y += cat->cVelY;
    cat->catsRect.x += cat->cVelX;

    if ((cat->catsRect.y + CATS_SIZE > 650) && cat->is_stone == false) {
        cat->catsRect.y -= cat->cVelY;
        cat->is_bubble = true;
        Mix_PlayChannel(-1, cat->CatFell, 0);

        if (cat->catsRect.x < WINDOW_WIDTH / 2) {
            cat->cVelX -= 2;
            cat->cVelY *= -1;
        }
        else {
            cat->cVelX += 2;
            cat->cVelY *= -1;
        }
    }
    if (SDL_HasIntersection(&cat->catsRect, &player->playerRect) && cat->is_stone == false) {
        Mix_PlayChannel(0, catManager->CatMeow, 0);
        cat->catsRect.y = -100;
        cat->catsRect.x = catManager->CatPosArr[rand() % 12];
        counter->countnumber++;    
    }
}
void Cats_destroy(FallingCat *cat) {
    SDL_DestroyTexture(cat->FallingCat);
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
        Cat_move(catManager->cats[i], player, catManager, counter);

        if (catManager->cats[i]->catsRect.x <= 0 || catManager->cats[i]->catsRect.x >= WINDOW_WIDTH) {
            destroy_CollidedCat(catManager, i);
            --i;
        }
        else if (SDL_HasIntersection(&catManager->cats[i]->catsRect, &player->playerRect) && catManager->cats[i]->is_stone) {
            Mix_PlayChannel(0, catManager->StoneColl, 0);
            counter->countHP++;
            destroy_CollidedCat(catManager, i);
            --i;
        }
        else if (catManager->cats[i]->catsRect.y >= 550 && catManager->cats[i]->is_stone) {
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
    Mix_FreeChunk(catManager->StoneSpawn);
    Mix_FreeChunk(catManager->StoneColl);
    free(catManager->CatPosArr);
    free(catManager->StonesPosArr);
    free(catManager->cats);
    free(catManager);
}
void Cat_show(FallingCat *cat, SDL_Renderer* gRenderer, int bcat) {
    if(!cat->is_bubble) {
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
