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
                // cout << event.button.x << " ; " << event.button.y << "(" << coord << ")" << endl;

                if (board->getType(coord) != ' ' && board->getColor(coord) == getTurnColor())
                {
                    SDL_SetCursor(_playCursor);

                    if (event.type == SDL_MOUSEBUTTONDOWN)
                        _dropped = false, _sourceCoord = coord;
                }
                else
                    SDL_SetCursor(_normalCursor);
                
                if (event.type == SDL_MOUSEBUTTONUP)
                {
                    _input.obj = board->getType(_sourceCoord);
                    _input.src = _sourceCoord;
                    _input.dest = coord;

                    _dropped = true;
                    _sourceCoord.clear();

                    return (0);
                }
            }
            loadBoard(board, event.button.x, event.button.y);
            displayFrame();
        }
    }
    return (0);
}
