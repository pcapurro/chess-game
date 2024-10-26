#include "visualGame.hpp"

int visualGame::waitForEvent(const chessBoard *board)
{
    SDL_Event   event;
    string      coord;

    while (1)
    {
        if (SDL_PollEvent(&event) == true)
        {
            if (event.type == SDL_QUIT)
                return (1);
            else
            {
                cout << event.button.x << " ; " << event.button.y << endl;

                coord = getCoord(event.button.x, event.button.y);
                if (board->getType(coord) != ' ')
                    ;
            }
        }
    }
    return (0);
}
