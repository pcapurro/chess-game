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

    mainRenderer = SDL_CreateRenderer(mainWindow, -1, \
        SDL_RENDERER_ACCELERATED);
}
