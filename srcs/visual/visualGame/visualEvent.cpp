#include "visualGame.hpp"

int VisualGame::waitForEvent(const chessBoard *board)
{
    SDL_Event   event;

    while (1)
    {
        if (SDL_PollEvent(&event) == true)
        {
            if (event.type == SDL_QUIT)
                return (1);
            else
                ;
        }
    }
    return (0);
}
