#include "Header_main.h"
SDL_Window* window;
GameState* PBState;
/*int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){   ��� ������� �� �����*/
int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    window = SDL_CreateWindow("PB_MENU_TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    
    PBState = (GameState*)malloc(sizeof(GameState));
    PBState->run = MENU;
    PBState->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    PBState->handCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    PBState->arrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    PBState->bgMusic = NULL;
    PBState->volume = MAX_VOLUME / 2;
    
    while (PBState->run !=-1) {
        switch (PBState->run)
        {
        case MENU:
            menu(PBState);
            break;
        case INTRO:
            while (SDL_PollEvent(&PBState->event)) {
                if (PBState->event.type == SDL_QUIT) {
                    PBState->run = -1;
                }  
            }
            break;
        case LEVEL1:
            level1(PBState);
            break;
        case LEVEL2:
            while (SDL_PollEvent(&PBState->event)) {
                if (PBState->event.type == SDL_QUIT) {
                    PBState->run = -1;
                }
            }
            break;
        case LEVEL3:
            while (SDL_PollEvent(&PBState->event)) {
                if (PBState->event.type == SDL_QUIT) {
                    PBState->run = -1;
                }
            }
            break;
        default:
            break;
        }  
        SDL_RenderPresent(PBState->renderer);
        SDL_Delay(1000 / 60);
    }
    destroyWindow(PBState, window);
    return 0;
}