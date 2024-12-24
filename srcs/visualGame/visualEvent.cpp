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
    obj = getRectangle(coord, "promotion");

    displayPromotion(types.at(i), coord);

    while (1)
    {
        if (SDL_PollEvent(&event) == true)
        {
            if (event.type == SDL_QUIT)
                return ("end");

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
    SDL_RenderPresent(_mainRenderer);
    return (coord + types.at(i));
}

string  visualGame::waitForEvent(void)
{
    SDL_Event   event;
    string      coord;

    // activObj.x = _width / 80, activObj.y = _height - (_height / 11);
    // activObj.w = (_width / 26), activObj.h = (_height / 35);

    while (1)
    {
        if (SDL_PollEvent(&event) == true)
        {
            if (event.type == SDL_QUIT)
                return ("end");

            if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP
                || event.type == SDL_MOUSEMOTION)
            {
                coord = getCoord(event.button.x, event.button.y);
                if ((_board->getType(coord) != ' ' && _board->getColor(coord) == getTurnColor())
                    || (event.button.x >= _width - (_width / 16) && event.button.x <= _width && event.button.y >= _height - (_height / 16) && event.button.y <= _height)
                    || (event.button.x >= _width / 80 && event.button.x <= _width / 20 && event.button.y >= _height - (_height / 11) && event.button.y <= _height - (_height / 16)))
                {
                    SDL_SetCursor(_playCursor);
                    if (event.type == SDL_MOUSEBUTTONDOWN && coord != "none")
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
                        if (_droppedSrc == "none" || coord == "none" || _clickSrc == "none" || coord == "")
                        {
                            if (event.button.x >= _width - (_width / 16) && event.button.x <= _width
                                && event.button.y >= _height - (_height / 16) && event.button.y <= _height)
                                ++_boardColor == COLOR_NB ? _boardColor = 0 : _boardColor;

                            if ((event.button.x >= _width / 80 && event.button.x <= _width / 20
                                && event.button.y >= _height - (_height / 11) && event.button.y <= _height - (_height / 16)))
                                _evaluation = !_evaluation;
                            
                            return ("none");
                        }

                        _droppedDest = coord;
                        if (_droppedSrc == "")
                        {
                            _droppedSrc = _clickSrc;
                            if (_board->isLegal(_board->getType(_droppedSrc) + _droppedSrc + _droppedDest))
                                displayMoveAnimation(_droppedSrc + _droppedDest);
                        }

                        if (isPromotion(coord) == true
                            && _board->isLegal(_board->getType(_droppedSrc) + _droppedSrc + _droppedDest + 'Q') == true)
                            coord = waitForPromotion(coord);

                        return (getInput(coord));
                    }
                }
                displayGame(event.button.x, event.button.y);
                SDL_RenderPresent(_mainRenderer);
            }
        }
    }
    return ("error");
}
