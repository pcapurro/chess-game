#include "../include/shellChess.hpp"

void    initializeGame(t_game *mainStr)
{
    mainStr->mainWindow = SDL_CreateWindow("shell-chess", 100, 100, \
        700, 700, SDL_WINDOW_SHOWN);

    mainStr->mainRenderer = SDL_CreateRenderer(mainStr->mainWindow, -1, \
        SDL_RENDERER_ACCELERATED);
    
    IMG_Init(IMG_INIT_PNG);
}

int visualGame(void)
{
    t_game  *mainStr;

    mainStr = new (std::nothrow) t_game;
    if (mainStr == nullptr)
        return (1);
    else
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
            return (1);
        initializeGame(mainStr);

        SDL_Surface *boardSurface;
        boardSurface = IMG_Load("./materials/board.png");

        SDL_Texture *boardTexture;
        boardTexture = SDL_CreateTextureFromSurface(mainStr->mainRenderer, boardSurface);
        SDL_FreeSurface(boardSurface);

        SDL_RenderClear(mainStr->mainRenderer);
        SDL_RenderCopy(mainStr->mainRenderer, boardTexture, NULL, NULL);
        SDL_RenderPresent(mainStr->mainRenderer);

        SDL_Delay(6000);

        SDL_DestroyWindow(mainStr->mainWindow);
        SDL_Quit();
    }

    return (0);
}

// https://alexandre-laurent.developpez.com/tutoriels/sdl-2/creer-premieres-fenetres/