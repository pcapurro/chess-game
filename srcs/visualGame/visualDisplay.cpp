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
        color = "black";
    else
        color = "white";

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

void    visualGame::loadBoard(const int cx, const int cy)
{
    SDL_Rect    obj;

    obj.h = _height, obj.w = _width, obj.x = 0, obj.y = 0;

    if (_aiSide != 0)
        SDL_RenderCopy(_mainRenderer, _whiteBoardTexture, NULL, &obj);
    else
        SDL_RenderCopy(_mainRenderer, _blackBoardTexture, NULL, &obj);

    obj.h = _height / 10, obj.w = _width / 10;

    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            string coords = string(1, "hgfedcba"[k]) + string(1, "87654321"[i]);
            char type = _board->getType(coords);
            string color = _board->getColor(coords);

            if (type != ' ')
            {
                if (coords != _droppedSrc)
                    obj = getRectangle(coords);
                else
                    obj.x = cx - ((_width / 10) / 2), obj.y = cy - ((_height / 10) / 2);
                
                SDL_RenderCopy(_mainRenderer, getTexture(type, color), \
                    NULL, &obj);
            }
        }
    }
}

void    visualGame::displayGame(const int cx, const int cy)
{
    int stateValue = _board->getStateValue();

    SDL_RenderClear(_mainRenderer);

    loadBoard(cx, cy);
    loadText(stateValue);
    loadArrow(stateValue);

    SDL_RenderPresent(_mainRenderer);
}
