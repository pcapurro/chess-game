#include "visualGame.hpp"

string visualGame::getInput(const string coord)
{
    string  input;

    if (coord == "end" || coord == "none" || coord == "error")
        return (coord);

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
    _droppedDest.clear();

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
    int             i = 0;
    string          coords;
    vector<char>    types;
    SDL_Event       event;
    SDL_Rect        obj;

    types.push_back('Q'), types.push_back('B'), types.push_back('N'), types.push_back('R');
    obj = getRectangle(coord, 0, 0, "promotion");

    displayPromotion(types.at(i), coord);

    while (1)
    {
        if (SDL_PollEvent(&event) == true)
        {
            if (event.type == SDL_QUIT)
                return (string("end"));

            coords = getCoord(event.button.x, event.button.y);

            if (isAbovePromotion(event.button.x, event.button.y, obj) == true)
            {
                SDL_SetCursor(_playCursor);

                if (event.type == SDL_MOUSEBUTTONUP)
                {
                    if (event.button.x > obj.x && event.button.x < obj.x + (_width / 40)
                        && event.button.y < obj.y + (_height / 16) && i != 0)
                        i--;
                    if (event.button.x > obj.x + (_width / 9) && event.button.x < (obj.x + obj.w)
                        && event.button.y < obj.y + (_height / 16) && i != 3)
                        i++;

                    if (event.button.x > obj.x + (_width / 25) && event.button.x < (obj.x + obj.w) - (_width / 25)
                        && event.button.y > obj.y + (_height / 16) && event.button.y < (obj.y + obj.h))
                        break ;
                    
                    displayPromotion(types.at(i), coord);
                }
            }
            else
                SDL_SetCursor(_normalCursor);
        }
    }
    displayGame();
    return (coord + types.at(i));
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
                        if (_droppedSrc == "none" || coord == "none"
                            || coord == "")
                            return ("none");
                        if (_droppedSrc == "")
                            _droppedSrc = _clickSrc;

                        _droppedDest = coord;

                        if (isPromotion(coord) == true)
                            coord = waitForPromotion(coord);

                        return (getInput(coord));
                    }
                }
                displayGame(event.button.x, event.button.y);
            }
        }
    }
    return ("error");
}
