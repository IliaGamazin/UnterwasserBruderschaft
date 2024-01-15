#include "./ExitCar.h"

// ExitCar

ExitCar* ExitCar_new(SDL_Renderer* r){
    ExitCar* Car;
    Car = (ExitCar*)malloc(sizeof(ExitCar));
    Car->carRect = createRect(600, 600, 214, 94);
    Car->carTex = IMG_LoadTexture(r, "media/img/carExit.png");
    Car->doorRect = createRect(672, 606, 52, 18);
    Car->doorTex = IMG_LoadTexture(r, "media/img/doorExit.png");
    Car->doorCollider = createRect(600, 400, 214, 294);
    Car->seatCollider = createRect(672, 570, 50, 50);
    Car->doorAngle = 0;
    Car->isOpened = false;
    Car->openSound = Mix_LoadWAV("");
    Car->isPlayingSound = 0;
    return Car;
}
void ExitCar_update(ExitCar* Car, SDL_Point PlayerCenter){
    if(Car->isOpened){
        if (SDL_PointInRect(&PlayerCenter, &Car->doorCollider) && Car->doorAngle > -90)
        {
            Car->doorAngle -= 5;
        }
        else if(!SDL_PointInRect(&PlayerCenter, &Car->doorCollider) && Car->doorAngle < 0){
            Car->doorAngle += 5;
        }
    }
}
void ExitCar_render(SDL_Renderer* r, ExitCar* Car){
    SDL_Point doorAnchor = {0, 0};
    SDL_RenderCopy(r,Car->carTex, NULL, &Car->carRect);
    SDL_RenderCopyEx(r, Car->doorTex, NULL, &Car->doorRect, Car->doorAngle, &doorAnchor, SDL_FLIP_NONE);
}
void ExitCar_destroy(ExitCar* Car){
    SDL_DestroyTexture(Car->carTex);
    SDL_DestroyTexture(Car->doorTex);
    Mix_FreeChunk(Car->openSound);
    free(Car);
}