#include "../inc/ExitCar.h"

// ExitCar

ExitCar *ExitCar_new(SDL_Renderer *r){
    ExitCar *Car;
    Car = (ExitCar*)malloc(sizeof(ExitCar));
    Car->car_rect = Rect_new(200, 960, 214, 94);
    Car->car_tex = IMG_LoadTexture(r, "media/img/carExit.png");
    Car->door_rect = Rect_new(Car->car_rect.x + 72, Car->car_rect.y + 6, 52, 18);
    Car->door_tex = IMG_LoadTexture(r, "media/img/doorExit.png");
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

void ExitCar_render(SDL_Renderer *r, ExitCar *Car, Camera camera){
    // Camera's offset
    SDL_Rect adjustedCarRect = {
        Car->car_rect.x - camera.position.x,
        Car->car_rect.y - camera.position.y,
        Car->car_rect.w,
        Car->car_rect.h
    };

    // Door's position by the camera's offset
    SDL_Rect adjustedDoorRect = {
        Car->door_rect.x - camera.position.x,
        Car->door_rect.y - camera.position.y,
        Car->door_rect.w,
        Car->door_rect.h
    };

    //  Anchor point relative to the adjusted door's position
    SDL_Point door_anchor = {
        (int)(adjustedDoorRect.x + Car->door_rect.w / 2),
        (int)(adjustedDoorRect.y + Car->door_rect.h / 2)
    };

    // Render the car and the door
    SDL_RenderCopy(r, Car->car_tex, NULL, &adjustedCarRect);
    SDL_RenderCopyEx(r, Car->door_tex, NULL, &adjustedDoorRect, Car->door_angle, &door_anchor, SDL_FLIP_NONE);
}

void ExitCar_destroy(ExitCar *Car){
    SDL_DestroyTexture(Car->car_tex);
    SDL_DestroyTexture(Car->door_tex);
    Mix_FreeChunk(Car->open_sound);
    free(Car);
}

