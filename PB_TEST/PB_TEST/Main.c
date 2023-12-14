#include "header.h"
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* bgTexture;
SDL_Rect bgRect;
SDL_Event event;

/*int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) { */ /*ДЛЯ ЗАПУСКА НА ВИНДЕ*/
int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_MP3);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    window = SDL_CreateWindow("PB_MENU_TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool quit = false;
    int run = 0; /*Значение, которое возвращает функция уровня*/

    bool quitTimeFlag = false;
    int quitButtonSpeed = 1;
    int volume = 60;
    int scene = MENU;
    
    Mix_PlayMusic(Mix_LoadMUS("media/sound/nightcall.mp3"), 0);
    bgTexture = IMG_LoadTexture(renderer, "media/img/menu_bg.png");
    bgRect = createRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_QueryTexture(bgTexture, NULL, NULL, &bgRect.w, &bgRect.h);

    Button* buttonArr = fillButtonArr((WINDOW_WIDTH-BUTTON_WIDTH)-10, BUTTON_GAP * 1.5, BUTTON_WIDTH, BUTTON_HEIGHT);
    SoundBar* Bar = createSoundBar(0,0,volume*2, 30, renderer);
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            SDL_Point mousePoint = { mouseX, mouseY };
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (!quitTimeFlag)
            {
                handleButtonPointing(mousePoint, buttonArr, renderer);
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                for (int i = 0; i < BUTTON_COUNT; i++)
                {
                    if (SDL_PointInRect(&mousePoint, &buttonArr[i].buttonRect) == true) {
                        switch (i)
                        {
                        case START_BUTTON:
                            scene = LEVEL1;
                            printf("\nStart button");
                            break;
                        case FIRST_LEVEL_BUTTON:
                            printf("\nFirst level");
                            break;
                        case SECOND_LEVEL_BUTTON:
                            printf("\nSecond level");
                            break;
                        case THIRD_LEVEL_BUTTON:
                            printf("\nThird level");
                            break;
                        case EXIT_BUTTON:
                            if (!quitTimeFlag)
                            {
                                printf("\nExit button");
                                quitTimeFlag = true;
                                Mix_PlayChannel(-1, Mix_LoadWAV("media/sound/carPass.wav"), 0);
                            }
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                
                switch (event.key.keysym.sym) {
                case SDLK_EQUALS:
                    if (volume < 120) {
                        volume += 12;

                    }
                    else {
                        volume = 120;
                    }
                    break;
                case SDLK_MINUS:
                    if (volume > 0) {
                        volume -= 12; 
                    }
                    else {
                        volume = 0;
                    }
                    break;
                }
                printf("\n Volume: %d", volume);
                Mix_Volume(-1, volume);
                Mix_VolumeMusic(volume);
            }
        }
        if (quitTimeFlag == true)
        {
            buttonArr[BUTTON_COUNT - 1].buttonRect.x -= quitButtonSpeed / 3;
            quitButtonSpeed += 1;
            if (buttonArr[BUTTON_COUNT - 1].buttonRect.x < -BUTTON_WIDTH)
            {
                quit = true;
            }
        }
        updateSoundBar(Bar, volume);
        SDL_RenderCopy(renderer, bgTexture, NULL, &bgRect);
        SDL_RenderCopy(renderer, Bar->barTexture, NULL, &Bar->barRect);
        for (int i = 0; i < BUTTON_COUNT; i++)
        {
            showButton(renderer, buttonArr[i]);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 120);
    }
    destroyMenu(renderer, window, buttonArr, bgTexture, Bar);

    return 0;
}