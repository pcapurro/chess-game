#include "../include/shellChess.hpp"

int visualGame(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return (systemFailed());
    else
    {
        SDL_Window  *mainWindow;

        mainWindow = nullptr;
        mainWindow = SDL_CreateWindow("shell-chess", 100, 100, \
                    1280, 720, SDL_WINDOW_SHOWN);
        if (!mainWindow || mainWindow == nullptr)
            return (systemFailed());

        SDL_Delay(10000);

        SDL_DestroyWindow(mainWindow);
        SDL_Quit();
    }

    return (0);
}
