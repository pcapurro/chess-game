#include "visualGame.hpp"

void    visualGame::loadArrow(const int value)
{
    SDL_Rect    obj;

    obj.x = _width - (_width / 12), obj.y = 0;
    obj.w = _width / 12, obj.h = _height / 12;
    SDL_RenderCopy(_mainRenderer, _arrow.getTexture(), NULL, &obj);
}

void    visualGame::loadText(const int value)
{
    SDL_Rect    obj;
    string      color;
    
    if (_turn % 2 == 0)
        color = "white";
    else
        color = "black";

    obj.x = _width / 5 + (_width / 266), obj.y = _height / 57;
    obj.w = _width / 2, obj.h = _height / 16;
    if (value == 0)
    {
        if (color == "white")
            SDL_RenderCopy(_mainRenderer, _texts.whiteToPlay.getTexture(), NULL, &obj);
        if (color == "black")
            SDL_RenderCopy(_mainRenderer, _texts.blackToPlay.getTexture(), NULL, &obj);
    }
    if (value == 1)
    {
        if (color == "white")
            SDL_RenderCopy(_mainRenderer, _texts.blackWon.getTexture(), NULL, &obj);
        if (color == "black")
            SDL_RenderCopy(_mainRenderer, _texts.whiteWon.getTexture(), NULL, &obj);
    }

    if (value == 2)
        SDL_RenderCopy(_mainRenderer, _texts.draw.getTexture(), NULL, &obj);
}

void    visualGame::loadEvaluation(const int value)
{
    SDL_Rect    activObj;
    SDL_Rect    evalObj;

    activObj.x = _width / 80, activObj.y = _height - (_height / 11);
    activObj.w = (_width / 26), activObj.h = (_height / 35);

    evalObj.x = _width / 40, evalObj.y = _height / 10;
    evalObj.w = _width / 26, evalObj.h = _height - (_height / 5);

    if (_evaluation == true && value == 0)
    {
        int score;

        SDL_SetRenderDrawColor(_mainRenderer, 76, 153, 0, 255);
        SDL_RenderFillRect(_mainRenderer, &activObj);

        if (_sandBoxMode == false && _aiSide % 2 == 0)
        {
            SDL_SetRenderDrawColor(_mainRenderer, 0, 0, 0, 255);
            SDL_RenderFillRect(_mainRenderer, &evalObj);
            SDL_SetRenderDrawColor(_mainRenderer, 255, 255, 255, 255);
            score = _whiteScore;
        }
        else
        {
            SDL_SetRenderDrawColor(_mainRenderer, 255, 255, 255, 255);
            SDL_RenderFillRect(_mainRenderer, &evalObj);
            SDL_SetRenderDrawColor(_mainRenderer, 0, 0, 0, 255);
            score = _blackScore;
        }

        if (_whiteScore + _blackScore == 0)
            _whiteScore = 50, _blackScore = 50, score = 50;

        evalObj.h = (score * (_height - (_height / 5))) / (_whiteScore + _blackScore);
        SDL_RenderFillRect(_mainRenderer, &evalObj);
    }
    else
    {
        SDL_SetRenderDrawColor(_mainRenderer, 153, 0, 0, 255);
        SDL_RenderFillRect(_mainRenderer, &activObj);

        SDL_SetRenderDrawColor(_mainRenderer, 164, 164, 164, 255);
        SDL_RenderFillRect(_mainRenderer, &evalObj);
    }
}

void    visualGame::loadMapColors(void)
{
    int         colors[COLOR_NB][3] = COLORS;
    SDL_Rect    obj;

    obj = getRectangle("", "default");

    _boardColors.clear();
    _boardColors.push_back(colors[_boardColor][0]);
    _boardColors.push_back(colors[_boardColor][1]);
    _boardColors.push_back(colors[_boardColor][2]);

    obj.w = _width / 10, obj.h = _height / 10;
    obj.x = _width - (_width / 14), obj.y = _height - (_height / 10);
    SDL_SetRenderDrawColor(_mainRenderer, _boardColors.at(0), _boardColors.at(1), _boardColors.at(2), 255);
    SDL_RenderFillRect(_mainRenderer, &obj);
}

void    visualGame::loadPath(void)
{
    SDL_Rect    obj;

    if (_droppedSrc != "")
    {
        obj = getRectangle(_droppedSrc);
        SDL_SetRenderDrawColor(_mainRenderer, 255, 255, 255, 128);
        SDL_RenderFillRect(_mainRenderer, &obj);

        SDL_SetRenderDrawColor(_mainRenderer, 0, 255, 128, 100);
        SDL_RenderFillRect(_mainRenderer, &obj);
    }

    if (_lastMove != "")
    {
        obj = getRectangle(string(1, _lastMove[0]) + _lastMove[1]);
        SDL_SetRenderDrawColor(_mainRenderer, 255, 255, 255, 128);
        SDL_RenderFillRect(_mainRenderer, &obj);

        SDL_SetRenderDrawColor(_mainRenderer, 204, 204, 0, 100);
        SDL_RenderFillRect(_mainRenderer, &obj);

        obj = getRectangle(string(1, _lastMove[2]) + _lastMove[3]);
        SDL_SetRenderDrawColor(_mainRenderer, 255, 255, 255, 128);
        SDL_RenderFillRect(_mainRenderer, &obj);

        SDL_SetRenderDrawColor(_mainRenderer, 204, 204, 0, 100);
        SDL_RenderFillRect(_mainRenderer, &obj);
    }
}

void    visualGame::loadMap(void)
{
    SDL_Rect    obj;
    bool        state;

    loadMapColors();
    obj = getRectangle("", "default");
    SDL_RenderCopy(_mainRenderer, _boardTexture.getTexture(), NULL, &obj);

    state = true;
    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            string coords = string(1, "hgfedcba"[k]) + string(1, "87654321"[i]);

            if ((state == true && k % 2 == 0)
                || (state == false && k % 2 != 0))
            {
                obj = getRectangle(coords);
                SDL_SetRenderDrawColor(_mainRenderer, _boardColors.at(0), _boardColors.at(1), _boardColors.at(2), 255);
                SDL_RenderFillRect(_mainRenderer, &obj);
            }
        }
        state = !state;
    }
}

void    visualGame::loadCoords(void)
{
    visualTexture *letters[8] = {&_letters.a, &_letters.b, &_letters.c, &_letters.d, \
        &_letters.e, &_letters.f, &_letters.g, &_letters.h};
    visualTexture *numbers[8] = { &_numbers.one, &_numbers.two, &_numbers.three, &_numbers.four, \
        &_numbers.five, &_numbers.six, &_numbers.seven, &_numbers.eight };

    SDL_Rect    obj;

    obj = getRectangle("coords");
    if (_sandBoxMode == false && _aiSide % 2 == 0)
    {
        for (int i = 8; i != -1; i--)
            ;
        for (int i = 8; i != -1; i--)
            ;
    }
    else
    {
        for (int i = 0; i != 8; i++)
            ;
        for (int i = 0; i != 8; i++)
            ;
    }

}

void    visualGame::loadBoard(const string color, const int cx, const int cy)
{
    char        objType;
    string      coords;
    string      objColor;
    SDL_Rect    obj;

    obj.h = _height / 10, obj.w = _width / 10;

    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            coords = string(1, "hgfedcba"[k]) + string(1, "87654321"[i]);
            objType = _board->getType(coords);
            objColor = _board->getColor(coords);

            if (objType != ' ' && objColor == color && coords != _droppedDest)
            {
                if (coords != _droppedSrc)
                    obj = getRectangle(coords);
                else
                    obj.x = cx - ((_width / 14) / 2), obj.y = cy - ((_height / 10) / 2);

                if (obj.x > 0 && obj.y > 0 && obj.x < _width && obj.y << _height)
                    SDL_RenderCopy(_mainRenderer, getTexture(objType, objColor), NULL, &obj);
            }
        }
    }
}

void    visualGame::loadCheck(void)
{
    string      color;
    string      kingCoords;
    SDL_Rect    obj;

    _turn % 2 == 0 ? color = "white" : color = "black";
    kingCoords = getKingCoords(color);
    obj = getRectangle(getKingCoords(color));

    SDL_SetRenderDrawColor(_mainRenderer, 242, 255, 0, 255);
    SDL_RenderFillRect(_mainRenderer, &obj);
}

void    visualGame::loadDraw(void)
{
    string      color;
    SDL_Rect    obj;

    _turn % 2 == 0 ? color = "white" : color = "black";
    obj = getRectangle(getKingCoords(color));

    SDL_SetRenderDrawColor(_mainRenderer, 128, 128, 128, 255);
    SDL_RenderFillRect(_mainRenderer, &obj);

    _turn % 2 == 0 ? color = "black" : color = "white";
    obj = getRectangle(getKingCoords(color));

    SDL_SetRenderDrawColor(_mainRenderer, 128, 128, 128, 255);
    SDL_RenderFillRect(_mainRenderer, &obj);
}

void    visualGame::loadCheckMate(void)
{
    string      color;
    string      kingCoords;
    SDL_Rect    obj;

    _turn % 2 == 0 ? color = "white" : color = "black";
    kingCoords = getKingCoords(color);
    obj = getRectangle(getKingCoords(color));

    SDL_SetRenderDrawColor(_mainRenderer, 215, 0, 21, 255);
    SDL_RenderFillRect(_mainRenderer, &obj);

    obj = getRectangle(kingCoords);
    obj.h = obj.h / 3, obj.w = obj.w / 3;
    SDL_RenderCopy(_mainRenderer, getTexture('c', color), NULL, &obj);

    color == "white" ? color = "black" : color = "white";
    kingCoords = getKingCoords(color);
    obj = getRectangle(getKingCoords(color));

    SDL_SetRenderDrawColor(_mainRenderer, 0, 190, 60, 255);
    SDL_RenderFillRect(_mainRenderer, &obj);

    obj = getRectangle(kingCoords);
    obj.h = obj.h / 3, obj.w = obj.w / 3;
    SDL_RenderCopy(_mainRenderer, getTexture('c', color), NULL, &obj);
}

void    visualGame::displayMoveAnimation(const string move)
{
    int         destX, destY;
    string      src, dest;
    SDL_Rect    obj;

    src = string(1, move[0]) + move[1];
    dest = string(1, move[2]) + move[3];

    obj.x = getRectangle(src).x;
    obj.y = getRectangle(src).y;

    destX = getRectangle(dest).x;
    destY = getRectangle(dest).y;

    _droppedSrc = src;
    while (obj.y != destY || obj.x != destX)
    {
        if ((src[0] == dest[0] && src[1] != dest[1]) || (src[0] != dest[0] && src[1] != dest[1]))
            destY > obj.y ? obj.y++ : obj.y--;
        if ((src[0] != dest[0] && src[1] == dest[1]) || (src[0] != dest[0] && src[1] != dest[1]))
            destX > obj.x ? obj.x++ : obj.x--;

        displayGame(obj.x + ((_width / 14) / 2), obj.y + ((_height / 10) / 2));
        SDL_RenderPresent(_mainRenderer);
        usleep(500);
    }
}

void    visualGame::displayPromotion(const char type, const string coord)
{
    SDL_Rect    obj;
    string      color;

    displayGame();

    _turn % 2 == 0 ? color = "white" : color = "black";

    obj = getRectangle(coord);
    SDL_RenderCopy(_mainRenderer, getTexture(type, color), NULL, &obj);

    obj = getRectangle(coord, "promotion");
    SDL_RenderCopy(_mainRenderer, _promotion.getTexture(), NULL, &obj);

    SDL_RenderPresent(_mainRenderer);
}

void    visualGame::displayGame(const int cx, const int cy)
{
    int stateValue = _board->getStateValue();

    SDL_RenderClear(_mainRenderer);

    loadEvaluation(stateValue);
    loadMap();
    loadCoords();
    loadPath();

    if (_board->isItCheckMate() == true)
        loadCheckMate();
    else if (_board->isItCheck() == true)
        loadCheck();
    else if (_board->isItDraw() == true)
        loadDraw();

    if (_turn % 2 == 0)
        loadBoard("black", cx, cy), loadBoard("white", cx, cy);
    else
        loadBoard("white", cx, cy), loadBoard("black", cx, cy);

    loadText(stateValue);
    loadArrow(stateValue);
}
