#include "../include/shellChess.hpp"

int visualGame(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return (systemFailed());
    else
    {
        SDL_Window      *mainWindow;
        SDL_Renderer    *mainRenderer;

        mainWindow = SDL_CreateWindow("shell-chess", 100, 100, \
                    700, 700, SDL_WINDOW_SHOWN);

        mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

        IMG_Init(IMG_INIT_PNG);

        SDL_Surface *boardSurface;
        boardSurface = IMG_Load("./materials/board.png");

        SDL_Texture *boardTexture;
        boardTexture = SDL_CreateTextureFromSurface(mainRenderer, boardSurface);
        SDL_FreeSurface(boardSurface);

        SDL_RenderClear(mainRenderer);
        SDL_RenderCopy(mainRenderer, boardTexture, NULL, NULL);
        SDL_RenderPresent(mainRenderer);

        SDL_Delay(6000);

        SDL_DestroyWindow(mainWindow);
        SDL_Quit();
    }

    return (0);
}

// https://alexandre-laurent.developpez.com/tutoriels/sdl-2/creer-premieres-fenetres/