#include "visualGame.hpp"

int visualGame::loadInput(const string coord, const chessBoard *board)
{
    _input.obj = board->getType(_sourceCoord);
    _input.src = _sourceCoord;
    _input.dest = coord;
    _input.action = '-';

    if (_input.obj == 'K')
    {
        if ((_input.dest == "g1" && _input.src == "e1") || (_input.dest == "g8" && _input.src == "e8"))
            _input.dest = "O-O";
        if ((_input.dest == "c1" && _input.src == "e1") || (_input.dest == "c8" && _input.src == "e8"))
            _input.dest = "O-O-O";
    }

    _dropped = true;
    _sourceCoord.clear();

    return (0);
}

int visualGame::waitForNewGame(void)
{
    SDL_Event   event;

    while (1)
    {
        if (SDL_PollEvent(&event) == true)
        {
            if (event.type == SDL_QUIT 
                || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
                return (1);

            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                setNewDimensions(event.window.data1, event.window.data2);

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
                break ;
        }
    }
    return (0);
}

int visualGame::waitForEvent(const chessBoard *board)
{
    SDL_Event   event;
    string      coord;

    while (1)
    {
        if (SDL_PollEvent(&event) == true)
        {
            if (event.type == SDL_QUIT 
                || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
                return (1);
            else
            {
                coord = getCoord(event.button.x, event.button.y);
                if (board->getType(coord) != ' ' && board->getColor(coord) == getTurnColor())
                {
                    SDL_SetCursor(_playCursor);
                    if (event.type == SDL_MOUSEBUTTONDOWN)
                        _dropped = false, _sourceCoord = coord;
                }
                else
                    SDL_SetCursor(_normalCursor);

                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                    setNewDimensions(event.window.data1, event.window.data2);
                
                if (event.type == SDL_MOUSEBUTTONUP)
                    return (loadInput(coord, board));
            }
            displayGame(board, event.button.x, event.button.y);
        }
    }
    return (0);
}
