#ifndef TIMER_H 
#define TIMER_H 
 
#include "Libs.h" 
 
// Timer 
 
typedef struct s_Timer { 
    int current_time; 
    bool is_stopped; 
    int last_update_time; 
    SDL_Texture *tex; 
    SDL_Texture *colon_tex; 
}              t_Timer; 
 
t_Timer *timer_new(SDL_Renderer *r); 
void timer_update(t_Timer *Timer); 
void timer_render(t_Timer *Timer, SDL_Renderer *r); 
void timer_destroy(t_Timer *timer); 
 
#endif



