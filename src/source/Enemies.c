#include "../inc/header.h"

Stone *Stone_create(SDL_Renderer* gRenderer, int x) {
    Stone* stone = (Stone*)malloc(sizeof(Stone));

    stone->StoneRect.x = x;
    stone->StoneRect.y = -STONE_SIZE;
    stone->StoneRect.w = STONE_SIZE;
    stone->StoneRect.h = STONE_SIZE;
    stone->bVelX = STONE_VEL;

    stone->StoneTexture = IMG_LoadTexture(gRenderer, "images/bull.png");
    stone->StoneColl = Mix_LoadWAV("sound/bam.wav");

    return stone;
} 

StoneManager *StoneManager_create(int capacity) {
    StoneManager *stoneManager = (StoneManager*)malloc(sizeof(StoneManager));

    stoneManager->stones = (Stone**)malloc(capacity * sizeof(Stone*));
    stoneManager->StonesPosArr = (int*)malloc(STONES_POS_COUNT * sizeof(int));
    stoneManager->StonesPosArr[0] = 80;
    for (int i = 1; i < STONES_POS_COUNT; i++)
        stoneManager->StonesPosArr[i] = stoneManager->StonesPosArr[i - 1] + 150;

    stoneManager->capacity = capacity;
    stoneManager->count = 0;

    stoneManager->StoneSpawn = Mix_LoadWAV("sound/bullspawn.wav");

    return stoneManager;
}

void SpawnStone(StoneManager *stoneManager, SDL_Renderer* gRenderer) {
    if (stoneManager->count < stoneManager->capacity) {
        Stone *newStone = Stone_create(gRenderer, stoneManager->StonesPosArr[rand()%8]);
        stoneManager->stones[stoneManager->count++] = newStone;

        Mix_PlayChannel(0, stoneManager->StoneSpawn, 0);
    }
}
void Stone_move(Stone *stone, PlayerSecretLvL *player, StoneManager *stoneManager, Counter *counter) {
        stone->StoneRect.y += STONE_VEL;

    if (checkCollission(stone->StoneRect, player->playerRect)) {
        stone->StoneRect.y = -50;
        stone->StoneRect.x = stoneManager->StonesPosArr[rand() % 8];
        Mix_PlayChannel(2, stone->StoneColl, 0);

        counter->countHP++;
    }
}

void Stone_destroy(Stone *stone) {
    Mix_FreeChunk(stone->StoneColl);
    SDL_DestroyTexture(stone->StoneTexture);
    free(stone);
}

void StoneManager_destroy(StoneManager *stoneManager) {
    for (int i = 0; i < stoneManager->count; ++i) {
        Stone_destroy(stoneManager->stones[i]);
    }
    free(stoneManager->stones);
    free(stoneManager);
}

void destroy_CollidedStone(StoneManager *stoneManager, int index) {
    Stone_destroy(stoneManager->stones[index]);
    if (index < stoneManager->count - 1) {
        stoneManager->stones[index] = stoneManager->stones[stoneManager->count - 1];
    }
    --stoneManager->count;
}

void stoneManager_update(StoneManager *stoneManager, PlayerSecretLvL *player, Counter *counter) {
    for (int i = 0; i < stoneManager->count; i++) {
        Stone_move(stoneManager->stones[i], player, stoneManager, counter);

        if (stoneManager->stones[i]->StoneRect.y >= 650) {
            destroy_CollidedStone(stoneManager, i);
            --i;
        }
    }
}

void Stone_show(Stone *stone, SDL_Renderer* gRenderer) {
    SDL_RenderCopy(gRenderer, stone->StoneTexture, NULL, &stone->StoneRect);
}

void StoneArr_show(StoneManager *stoneManager, SDL_Renderer* gRenderer) {
    for (int i = 0; i < stoneManager->count; i++) {
        Stone_show(stoneManager->stones[i], gRenderer);
    }
}

void showAllStones(SDL_Renderer* gRenderer, StoneManager *stoneManager) {
    for (int i = 0; i < stoneManager->count; ++i) {
        Stone_show(stoneManager->stones[i], gRenderer);
    }
}
