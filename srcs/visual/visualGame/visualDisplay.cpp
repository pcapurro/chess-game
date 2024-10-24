#include "visualGame.hpp"

void    VisualGame::displayFrame(void)
{
    SDL_RenderClear(_mainRenderer);
    SDL_RenderCopy(_mainRenderer, _boardTexture, NULL, NULL);
    SDL_RenderPresent(_mainRenderer);

    SDL_Delay(4000);
}

void    VisualGame::loadBoard(void)
{
    ;
}
