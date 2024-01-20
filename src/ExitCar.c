#include "./ExitCar.h"

// ExitCar

ExitCar* ExitCar_new(SDL_Renderer* r){
    ExitCar* Car;
    Car = (ExitCar*)malloc(sizeof(ExitCar));
    Car->car_rect = createRect(600, 600, 214, 94);
    Car->car_tex = IMG_LoadTexture(r, "media/img/carExit.png");
    Car->door_rect = createRect(672, 606, 52, 18);
    Car->door_tex = IMG_LoadTexture(r, "media/img/doorExit.png");
    Car->door_collider = createRect(600, 400, 214, 294);
    Car->seat_collider = createRect(672, 570, 50, 50);
    Car->door_angle = 0;
    Car->is_opened = false;
    Car->open_sound = Mix_LoadWAV("");
    Car->is_playing_sound = 0;
    return Car;
}
void ExitCar_update(ExitCar* Car, SDL_Point PlayerCenter){
    if(Car->is_opened){
        if (SDL_PointInRect(&PlayerCenter, &Car->door_collider) && Car->door_angle > -90)
        {
            Car->door_angle -= 5;
        }
        else if(!SDL_PointInRect(&PlayerCenter, &Car->door_collider) && Car->door_angle < 0){
            Car->door_angle += 5;
        }
    }
}
void ExitCar_render(SDL_Renderer* r, ExitCar* Car){
    SDL_Point door_anchor = {0, 0};
    SDL_RenderCopy(r,Car->car_tex, NULL, &Car->car_rect);
    SDL_RenderCopyEx(r, Car->door_tex, NULL, &Car->door_rect, Car->door_angle, &door_anchor, SDL_FLIP_NONE);
}
void ExitCar_destroy(ExitCar* Car){
    SDL_DestroyTexture(Car->car_tex);
    SDL_DestroyTexture(Car->door_tex);
    Mix_FreeChunk(Car->open_sound);
    free(Car);
}