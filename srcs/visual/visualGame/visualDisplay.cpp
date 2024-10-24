#include "visualGame.hpp"

void    VisualGame::displayFrame()
{
    SDL_RenderClear(mainRenderer);
    SDL_RenderCopy(mainRenderer, boardTexture, NULL, NULL);
    SDL_RenderPresent(mainRenderer);

    SDL_Delay(6000);
}
