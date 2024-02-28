#include "../inc/ExitCar.h"

// ExitCar

ExitCar *ExitCar_new(SDL_Renderer *r){
    ExitCar *Car;
    Car = (ExitCar*)malloc(sizeof(ExitCar));
    Car->car_rect = Rect_new(200, 960, 214, 94);
    Car->car_tex = IMG_LoadTexture(r, "./resource/img/carExit.png");
    Car->door_rect = Rect_new(Car->car_rect.x + 72, Car->car_rect.y + 6, 52, 18);
    Car->door_tex = IMG_LoadTexture(r, "./resource/img/doorExit.png");
    Car->door_collider = Rect_new(Car->car_rect.x, Car->car_rect.y - 200, 214, 294);
    Car->seat_collider = Rect_new(Car->car_rect.x + 72, Car->car_rect.y - 30, 50, 50);
    Car->door_angle = 0;
    Car->is_opened = false;
    Car->open_sound = Mix_LoadWAV("");
    Car->is_playing_sound = 0;
    return Car;
}

void ExitCar_update(ExitCar *Car, SDL_Point PlayerCenter){
    if(Car->is_opened){
        if (SDL_PointInRect(&PlayerCenter, &Car->door_collider) && Car->door_angle > -90) {
            Car->door_angle -= 5;
        }
        else if(!SDL_PointInRect(&PlayerCenter, &Car->door_collider) && Car->door_angle < 0){
            Car->door_angle += 5;
        }
    }
}

void ExitCar_render(SDL_Renderer *renderer, ExitCar *car, Tilemap *map){
    SDL_Point door_anchor = {0, 0};
    SDL_SetRenderTarget(renderer, map->render_texture);
    SDL_RenderCopy(
        renderer,
        car->car_tex,
        NULL,
        &car->car_rect
    );
    SDL_RenderCopyEx(
        renderer,
        car->door_tex,
        NULL,
        &car->door_rect,
        car->door_angle,
        &door_anchor,
        SDL_FLIP_NONE
    );
    SDL_SetRenderTarget(renderer, NULL);
}

void ExitCar_destroy(ExitCar *Car){
    SDL_DestroyTexture(Car->car_tex);
    SDL_DestroyTexture(Car->door_tex);
    Mix_FreeChunk(Car->open_sound);
    free(Car);
}

