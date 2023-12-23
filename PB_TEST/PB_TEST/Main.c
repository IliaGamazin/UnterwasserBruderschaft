#include "Header.h"
SDL_Window* window;
SDL_Renderer* renderer;
Mix_Music* bgMusic;
SDL_Event event;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) { /* ��� ������� �� �����*/

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_MP3);
    SDL_Cursor* handCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_Cursor* arrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    window = SDL_CreateWindow("PB_MENU_TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);

    int run = 0; /*��������, ������� ���������� ������� ������*/

    while (run!=-1) {
        switch (run)
        {
        case MENU:
            run = menu(renderer, event, arrowCursor, handCursor, bgMusic);
            break;
        case INTRO:
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    run = -1;
                }
            }
            break;
        case LEVEL1:
            run = level1(renderer, event, arrowCursor, handCursor, bgMusic);
            break;
        case LEVEL2:
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    run = -1;
                }
            }
            break;
        case LEVEL3:
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    run = -1;
                }
            }
            break;
        default:
            break;
        }  
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 60);
    }
    destroyWindow(renderer, window, arrowCursor,handCursor);
    return 0;
}