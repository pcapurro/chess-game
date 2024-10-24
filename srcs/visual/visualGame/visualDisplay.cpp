#include "visualGame.hpp"

void    VisualGame::displayFrame()
{
    SDL_RenderClear(_mainRenderer);
    SDL_RenderCopy(_mainRenderer, _boardTexture, NULL, NULL);
    SDL_RenderPresent(_mainRenderer);

    SDL_Delay(4000);
}
