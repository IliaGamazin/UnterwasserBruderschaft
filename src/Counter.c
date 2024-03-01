#include "../inc/Counter.h"

Counter *Counter_create(SDL_Renderer* gRenderer) {
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
    counter->TensClip.w = 26;
    counter->TensClip.h = 40;

    counter->UnitsClip.x = 0;
    counter->UnitsClip.y = 0;
    counter->UnitsClip.w = 26;
    counter->UnitsClip.h = 40;

    counter->HPcounterRect.x = 0;
    counter->HPcounterRect.y = 70;
    counter->HPcounterRect.w = HPCOUNTER_WIDTH;
    counter->HPcounterRect.h = HPCOUNTER_HEIGHT;

    counter->HPcounterClip.x = 0;
    counter->HPcounterClip.y = 0;
    counter->HPcounterClip.w = HPCOUNTER_WIDTH;
    counter->HPcounterClip.h = HPCOUNTER_HEIGHT;

    counter->countnumber = 0; 
    counter->countHP = 0;

    counter->HPCounterTexture = IMG_LoadTexture(gRenderer, "resource/img/level3/catbread2.png");
    counter->TensTexture = IMG_LoadTexture(gRenderer, "resource/img/hud/num_sheet.png");
    counter->UnitsTexture = IMG_LoadTexture(gRenderer, "resource/img/hud/num_sheet.png");

    return counter;
}

void CounterSprites(Counter *counter) {
    counter->UnitsClip.x = 32 * (counter->countnumber % 10);
    counter->TensClip.x = 32 * (counter->countnumber / 10);

    counter->HPcounterClip.w = HPCOUNTER_WIDTH - 40 * counter->countHP;
    counter->HPcounterRect.w = HPCOUNTER_WIDTH - 40 * counter->countHP;
}

void Counter_destroy(Counter *counter) {
    SDL_DestroyTexture(counter->UnitsTexture);
    SDL_DestroyTexture(counter->TensTexture);
    SDL_DestroyTexture(counter->HPCounterTexture);
    free(counter);
}

void Counter_show(Counter *counter, SDL_Renderer* gRenderer) {
    SDL_RenderCopy(gRenderer, counter->UnitsTexture, &counter->UnitsClip, &counter->UnitsRect);
    SDL_RenderCopy(gRenderer, counter->TensTexture, &counter->TensClip, &counter->TensRect);
    SDL_RenderCopy(gRenderer, counter->HPCounterTexture, &counter->HPcounterClip, &counter->HPcounterRect);
}
