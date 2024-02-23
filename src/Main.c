#include "../include/Header_main.h"

SDL_Window* window;
GameState* PBState;

int main(void){

    // Libraries initialization

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    // Game state variables initialization

    window = SDL_CreateWindow("PB_MENU_TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    PBState = (GameState*)malloc(sizeof(GameState));
    PBState->run = MENU;
    PBState->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    PBState->handCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    PBState->arrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    PBState->bgMusic = NULL;
    CHARACTER_TYPE character = -1;

    // Game loop

    while (PBState->run != QUIT) {
        switch (PBState->run)
        {
        case MENU:
            menu(PBState);
            break;
        case INTRO_1:
            level_intro(PBState, INTRO_1);
            break;
        case INTRO_2:
            level_intro(PBState, INTRO_2);
            break;
        case LEVEL1_INTRO:
            level_intro(PBState, LEVEL1_INTRO);
            break;
        case LEVEL1_CHOOSE:
            character = ChooseCharacter(PBState, LEVEL1);
            break;
        case LEVEL1:
            level1(PBState, character);
            break;
        case LEVEL2_INTRO:
            level_intro(PBState, LEVEL2_INTRO);
            break;
        case LEVEL2_CHOOSE:
            character = ChooseCharacter(PBState, LEVEL2);
            break;
        case LEVEL2:
            level2(PBState, character);
            break;
        case LEVEL3:
            while (SDL_PollEvent(&PBState->event)) {
                if (PBState->event.type == SDL_QUIT) {
                    PBState->run = QUIT;
                }
            }
            break;
        default:
            break;
        }  
        SDL_RenderPresent(PBState->renderer);
    }
    
    destroyWindow(PBState, window);
    return 0;
}

