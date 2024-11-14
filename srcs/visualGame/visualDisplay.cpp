#include "visualGame.hpp"

void    visualGame::loadArrow(const int value)
{
    if (value != 0)
    {
        SDL_Rect    obj;

        obj.x = _width - (_width / 12), obj.y = 0;
        obj.w = _width / 12, obj.h = _height / 12;
        SDL_RenderCopy(_mainRenderer, _arrowTexture, NULL, &obj);
    }
}

void    visualGame::loadText(const int value)
{
    SDL_Rect    obj;
    string      color;
    
    if (_turn % 2 == 0)
        color = "white";
    else
        color = "black";

    obj.x = _width / 4, obj.y = _height / 80;
    obj.w = _width / 2, obj.h = _height / 16;
    if (value == 0)
    {
        if (color == "white")
            SDL_RenderCopy(_mainRenderer, _texts.whiteToPlay, NULL, &obj);
        if (color == "black")
            SDL_RenderCopy(_mainRenderer, _texts.blackToPlay, NULL, &obj);
    }
    if (value == 1)
    {
        if (color == "white")
            SDL_RenderCopy(_mainRenderer, _texts.blackWon, NULL, &obj);
        if (color == "black")
            SDL_RenderCopy(_mainRenderer, _texts.whiteWon, NULL, &obj);
    }

    if (value == 2)
        SDL_RenderCopy(_mainRenderer, _texts.draw, NULL, &obj);
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

            if (objType != ' ' && objColor == color
                && (_aiSide == -1 || _lastAiMove == "" || coords != (string(1, _lastAiMove[3]) + _lastAiMove[4])) || objType == 'N')
            {
                if (coords != _droppedSrc)
                    obj = getRectangle(coords);
                else
                    obj.x = cx - ((_width / 10) / 2), obj.y = cy - ((_height / 10) / 2);
                
                SDL_RenderCopy(_mainRenderer, getTexture(objType, objColor), \
                    NULL, &obj);
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

    SDL_SetRenderDrawColor(_mainRenderer, 0, 190, 60, 255);
    SDL_RenderFillRect(_mainRenderer, &obj);

    obj = getRectangle(kingCoords);
    obj.h = obj.h / 3, obj.w = obj.w / 3;
    SDL_RenderCopy(_mainRenderer, getTexture('c', color), NULL, &obj);
}

void    visualGame::loadMove(void)
{
    char        objType;
    string      objColor;

    string      src;
    string      dest;
    SDL_Rect    obj;

    cout << "ai move displaying... (" << _lastAiMove << ")" << endl;

    src = string(1, _lastAiMove[1]) + _lastAiMove[2];
    dest = string(1, _lastAiMove[3]) + _lastAiMove[4];
    objType = _board->getType(dest);
    objColor = _board->getColor(dest);

    int src_x = src[0] - 97;
    int src_y = atoi(src.c_str() + 1);

    int dest_x = dest[0] - 97;
    int dest_y = atoi(dest.c_str() + 1);

    // if (src[0] == dest[0] && src[1] != dest[1]) // déplacement vertical
        // ;

    // if (src[0] != dest[0] && src[1] == dest[1]) // déplacement horizontal
    //     ;
    // if (src[0] != dest[0] && src[1] != dest[1]) // déplacement diagonal
    //     ;
}

void    visualGame::displayGame(const int cx, const int cy)
{
    int         stateValue;
    SDL_Rect    obj;

    SDL_RenderClear(_mainRenderer);

    obj = getRectangle("", 0, 0, "default");

    SDL_SetRenderDrawColor(_mainRenderer, 0, 0, 0, 255);
    SDL_RenderFillRect(_mainRenderer, &obj);

    if (_aiSide != 0)
        SDL_RenderCopy(_mainRenderer, _whiteBoardTexture, NULL, &obj);
    else
        SDL_RenderCopy(_mainRenderer, _blackBoardTexture, NULL, &obj);

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

    if (_aiSide != -1 && _turn % 2 != _aiSide
        && _lastAiMove != "" && _lastAiMove[0] != 'N')
        loadMove(), _lastAiMove = "";

    stateValue = _board->getStateValue();

    loadText(stateValue);
    loadArrow(stateValue);

    SDL_RenderPresent(_mainRenderer);
}
