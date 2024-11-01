#include "visualGame.hpp"

int visualGame::loadInput(const string coord)
{
    _input.obj = _board->getType(_droppedSrc);
    _input.src = _droppedSrc;
    _input.dest = coord;

    if (_input.obj == 'K')
    {
        if ((_input.dest == "g1" && _input.src == "e1") || (_input.dest == "g8" && _input.src == "e8"))
            _input.dest = "O-O";
        if ((_input.dest == "c1" && _input.src == "e1") || (_input.dest == "c8" && _input.src == "e8"))
            _input.dest = "O-O-O";
    }

    if (_input.obj == 'P')
    {
        if (_input.dest[1] == '8' && _input.src[1] == '7'
            || _input.dest[1] == '1' && _input.src[1] == '2')
            _input.dest = _input.dest + 'Q';
    }

    _dropped = true;
    _droppedSrc.clear();

    return (0);
}

int visualGame::waitForNewGame(void)
{
    SDL_Event   event;

    while (1)
    {
        if (SDL_PollEvent(&event) == true)
        {
            if (event.type == SDL_QUIT)
                return (1);

            if (event.type == SDL_MOUSEBUTTONDOWN
                || event.type == SDL_MOUSEMOTION)
            {
                SDL_SetCursor(_playCursor);
                if (event.type == SDL_MOUSEBUTTONDOWN
                    && event.button.x > _width - (_width / 12) && event.button.y < _height / 12)
                    break ;
            }
            else
                SDL_SetCursor(_normalCursor);
        }
    }
    return (0);
}

int visualGame::waitForEvent(void)
{
    SDL_Event   event;
    string      coord;

    while (1)
    {
        if (SDL_PollEvent(&event) == true)
        {
            if (event.type == SDL_QUIT)
                return (1);

            if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP
                || event.type == SDL_MOUSEMOTION)
            {
                coord = getCoord(event.button.x, event.button.y);
                if (_board->getType(coord) != ' ' && _board->getColor(coord) == getTurnColor())
                {
                    SDL_SetCursor(_playCursor);
                    if (event.type == SDL_MOUSEBUTTONDOWN)
                        _dropped = false, _droppedSrc = coord;
                }
                else
                    SDL_SetCursor(_normalCursor);
                
                if (event.type == SDL_MOUSEBUTTONUP)
                    return (loadInput(coord));

                displayGame(event.button.x, event.button.y);
            }
        }
    }
    return (0);
}
