#include "visualGame.hpp"

string visualGame::getInput(const string coord)
{
    string  input;

    if (coord == "end" || coord == "none" || coord == "error")
        return (coord);

    _lastMove = _droppedSrc + coord;

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
            if (event.type == SDL_QUIT
                || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
                return (1);

            if (event.type == SDL_KEYDOWN
                && event.key.keysym.sym == SDLK_RETURN)
                break ;

            if (event.type == SDL_MOUSEBUTTONDOWN
                || event.type == SDL_MOUSEMOTION)
            {
                _x = event.button.x, _y = event.button.y;

                if (_x > 782 && _y < 60)
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
            if (event.type == SDL_QUIT
                || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
                return ("end");

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
                break ;

            _x = event.button.x, _y = event.button.y;
            coords = getCoord(_x, _y);

            if (isAbovePromotion(_x, _y, obj) == true)
            {
                SDL_SetCursor(_playCursor);

                if (event.type == SDL_MOUSEBUTTONUP)
                {
                    if (_x > obj.x && _x < obj.x + 20
                        && _y < obj.y + 50 && i != 0)
                        i--;
                    if (_x > obj.x + 88 && _x < (obj.x + obj.w)
                        && _y < obj.y + 50 && i != 3)
                        i++;

                    if (_x > obj.x + 32 && _x < (obj.x + obj.w) - 32
                        && _y > obj.y + 50 && _y < (obj.y + obj.h))
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

void    visualGame::reactKeyDown(const int key)
{
    if (_code == true)
    {
        _keyHistory.push_back(key);
        if (_keyHistory.size() > 11)
            _keyHistory.erase(_keyHistory.begin());

        if (isCodeDetected() == true)
            _code = false, cout << "You're pretty good!" << endl;
    }
}

void    visualGame::reactMouseMotion(void)
{
    if (isBoardTargetZone(_actualCoords, _x, _y) == true)
        SDL_SetCursor(_playCursor);
    else
        SDL_SetCursor(_normalCursor);
}

void    visualGame::reactMouseDown(const int key)
{
    if (isBoardTargetZone(_actualCoords, _x, _y) == true
        && _actualCoords != "none")
        _droppedSrc = _actualCoords;

    if (key == SDL_BUTTON_RIGHT)
        _visualCoords = !_visualCoords;

    if (isColorTargetZone(_actualCoords, _x, _y) == true)
        ++_boardColor == COLOR_NB ? _boardColor = 0 : _boardColor;
    if (isEvaluationTargetZone(_actualCoords, _x, _y) == true)
        _evaluation = !_evaluation;
}

void    visualGame::reactMouseUp(void)
{
    _droppedDest = _actualCoords;
    if (_droppedSrc == "")
    {
        _droppedSrc = _clickSrc;
        if (_board->isLegal(_board->getType(_droppedSrc) + _droppedSrc + _droppedDest))
            displayMoveAnimation(_droppedSrc + _droppedDest);
    }

    if (isPromotion(_actualCoords) == true
        && _board->isLegal(_board->getType(_droppedSrc) + _droppedSrc + _droppedDest + 'Q') == true)
        _actualCoords = waitForPromotion(_actualCoords);
}

string  visualGame::waitForEvent(void)
{
    SDL_Event   event;

    while (1)
    {
        if (SDL_PollEvent(&event) == true)
        {
            if (event.type == SDL_QUIT
                || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
                return ("end");

            _x = event.button.x, _y = event.button.y;
            _actualCoords = getCoord(_x, _y);

            if (event.type == SDL_KEYDOWN)
                reactKeyDown(event.key.keysym.sym);

            if (event.type == SDL_MOUSEMOTION)
                reactMouseMotion();

            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (_x > 780 && _y < 60)
                    return ("restart");
                reactMouseDown(event.button.button);
            }

            if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (_droppedSrc == _actualCoords)
                    _clickSrc = _actualCoords, _droppedSrc.clear();
                else
                    { reactMouseUp(); return (getInput(_actualCoords)); }
            }

            displayGame();
            SDL_RenderPresent(_mainRenderer);
        }
    }
    return ("error");
}
