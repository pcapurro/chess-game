#include "visualGame.hpp"

string visualGame::getInput(const string coord)
{
    string  input;

    input = input + _board->getType(_droppedSrc);
    input = input + _droppedSrc + coord;

    if (input[0] == 'K')
    {
        if ((coord == "g1" && _droppedSrc == "e1") || (coord == "g8" && _droppedSrc == "e8"))
            input[3] = 'O', input[4] = '-', input = input + "O";
        if ((coord == "c1" && _droppedSrc == "e1") || (coord == "c8" && _droppedSrc == "e8"))
            input[3] = 'O', input[4] = '-', input = input + "O-O";
    }

    _droppedSrc.clear();
    _clickSrc.clear();

    return (input);
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
                if (event.button.x > _width - (_width / 12) && event.button.y < _height / 12)
                {
                    if (event.type == SDL_MOUSEMOTION)
                        SDL_SetCursor(_playCursor);
                    if (event.type == SDL_MOUSEBUTTONDOWN)
                        break ;
                }
                else
                    SDL_SetCursor(_normalCursor);
            }
        }
    }
    return (0);
}

string  visualGame::waitForPromotion(const string coord)
{
    SDL_Event   event;

    cout << "waiting for promotion" << endl;
    while (1)
    {
        if (SDL_PollEvent(&event) == true)
        {
            if (event.type == SDL_QUIT)
                return (string("end"));

            if (event.type == SDL_MOUSEBUTTONUP)
                ;
        }
    }
}

string  visualGame::waitForEvent(void)
{
    SDL_Event   event;
    string      coord;

    while (1)
    {
        if (SDL_PollEvent(&event) == true)
        {
            if (event.type == SDL_QUIT)
                return (string("end"));

            if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP
                || event.type == SDL_MOUSEMOTION)
            {
                coord = getCoord(event.button.x, event.button.y);
                if (_board->getType(coord) != ' ' && _board->getColor(coord) == getTurnColor())
                {
                    SDL_SetCursor(_playCursor);
                    if (event.type == SDL_MOUSEBUTTONDOWN)
                        _droppedSrc = coord;
                }
                else
                    SDL_SetCursor(_normalCursor);
                
                if (event.type == SDL_MOUSEBUTTONUP)
                {
                    if (_droppedSrc == coord)
                        _clickSrc = coord, _droppedSrc.clear();
                    else
                    {
                        if (_droppedSrc == "none" || coord == "none")
                            return ("none");
                        if (_droppedSrc == "")
                            _droppedSrc = _clickSrc;

                        cout << "coord > " << coord << endl;

                        if (_board->getType(_droppedSrc) == 'P'
                            && ((coord[1] == '8' && _droppedSrc[1] == '7')
                            || (coord[1] == '1' && _droppedSrc[1] == '2')))
                            coord = waitForPromotion(coord);

                        return (getInput(coord));
                    }
                }

                displayGame(event.button.x, event.button.y);
            }
        }
    }
    return ("");
}
