#include "visualGame.hpp"

VisualGame::VisualGame()
{
    initializeGame();
    loadTextures();
}

void    VisualGame::initializeGame(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    
    mainWindow = SDL_CreateWindow("shell-chess", 100, 100, \
        700, 700, SDL_WINDOW_SHOWN);
    if (!mainWindow)
        ;

    mainRenderer = SDL_CreateRenderer(mainWindow, -1, \
        SDL_RENDERER_ACCELERATED);
    if (!mainRenderer)
        ;
}

void    VisualGame::displayFrame()
{
    SDL_RenderClear(mainRenderer);
    SDL_RenderCopy(mainRenderer, boardTexture, NULL, NULL);
    SDL_RenderPresent(mainRenderer);

    SDL_Delay(6000);
}
