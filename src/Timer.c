#include "../include/Timer.h"

// Timer create

t_Timer *timer_new(int limit_time, SDL_Renderer *r) {
    t_Timer *Timer = (t_Timer*)malloc(sizeof(t_Timer));
    Timer->limit_time = limit_time;
    Timer->current_time = 0;
    Timer->is_stopped = false;
    Timer->last_update_time = 0;
    Timer->tex = IMG_LoadTexture(r, "media/img/hud/num_sheet.png");

    return Timer;
}

// Timer update

void timer_update(t_Timer *Timer) {

    // Get time

    if (SDL_GetTicks() - Timer->last_update_time >= 1000) {
        Timer->current_time++;
        Timer->last_update_time = SDL_GetTicks();
    }

    // Stop if time has passed

    if (Timer->current_time <= Timer->limit_time) {
        Timer->is_stopped = true;
    }
}

void timer_render(t_Timer *Timer, SDL_Renderer *r) {
   // int minutes = Timer->current_time / 60;
    int seconds = Timer->current_time % 60;

    SDL_Rect rect = Rect_new(100, 100, 32, 35);
    SDL_Rect clip = Rect_new(32 * (seconds % 10), 0, 32, 35);
    SDL_RenderCopy(r, Timer->tex, &clip, &rect);
    
}

void timer_destroy(t_Timer *timer) {
    SDL_DestroyTexture(timer->tex);
    free(timer);
}


