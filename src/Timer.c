#include "../inc/Timer.h" 

// Timer create 

t_Timer *timer_new(SDL_Renderer *r) { 
    t_Timer *Timer = (t_Timer*)malloc(sizeof(t_Timer)); 
    Timer->current_time = 120; 
    Timer->is_stopped = false; 
    Timer->last_update_time = 0; 
    Timer->tex = IMG_LoadTexture(r, "./resource/img/hud/num_sheet.png"); 
    Timer->colon_tex = IMG_LoadTexture(r, "./resource/img/level2/colon_tex.png");   
    return Timer; 
}

// Timer update 

void timer_update(t_Timer *Timer) {
    if (SDL_GetTicks() - Timer->last_update_time >= 1000 && Timer->current_time > 0) {
        Timer->current_time--;
        Timer->last_update_time = SDL_GetTicks();
    }

    if (Timer->current_time == 0) {
        Timer->is_stopped = true;
    }
}

// Timer render

void timer_render(t_Timer *Timer, SDL_Renderer *r) {
    int minutes = Timer->current_time / 60;
    int seconds = Timer->current_time % 60;

     // Render minutes
    SDL_Rect rect = Rect_new(100, 100, 32, 35);
    SDL_Rect clip = Rect_new(32 * (minutes % 10), 0, 32, 35);
    SDL_RenderCopy(r, Timer->tex, &clip, &rect);

    // Render colon
    rect.x += 32;
    SDL_RenderCopy(r, Timer->colon_tex, NULL, &rect); 

    // Render seconds
    rect.x += 32;
    clip = Rect_new(32 * (seconds / 10), 0, 32, 35);
    SDL_RenderCopy(r, Timer->tex, &clip, &rect);

    rect.x += 32;
    clip = Rect_new(32 * (seconds % 10), 0, 32, 35);
    SDL_RenderCopy(r, Timer->tex, &clip, &rect);
}

// Timer destroy

void timer_destroy(t_Timer *timer) {
    SDL_DestroyTexture(timer->tex);
    free(timer);
}

