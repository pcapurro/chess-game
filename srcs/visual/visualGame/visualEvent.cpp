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
                coord = getCoord(event.button.x, event.button.y);
                cout << event.button.x << " ; " << event.button.y << "(" << coord << ")" << endl;

                if (board->getType(coord) != ' ' && board->getColor(coord) == getTurnColor())
                    SDL_SetCursor(_playCursor);
                else
                    SDL_SetCursor(_normalCursor);
            }
        }
    }
    return (0);
}
