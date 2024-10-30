#include "visualGame.hpp"

SDL_Texture *visualGame::getTexture(const char type, const string color) const
{
    if (color == "white")
    {
        if (type == 'K')
            return (_whiteTextures.king);
        if (type == 'Q')
            return (_whiteTextures.queen);
        if (type == 'R')
            return (_whiteTextures.rook);
        if (type == 'B')
            return (_whiteTextures.bishop);
        if (type == 'N')
            return (_whiteTextures.knight);
        if (type == 'P')
            return (_whiteTextures.pawn);
    }
    if (color == "black")
    {
        if (type == 'K')
            return (_blackTextures.king);
        if (type == 'Q')
            return (_blackTextures.queen);
        if (type == 'R')
            return (_blackTextures.rook);
        if (type == 'B')
            return (_blackTextures.bishop);
        if (type == 'N')
            return (_blackTextures.knight);
        if (type == 'P')
            return (_blackTextures.pawn);
    }
    return (nullptr);
}

SDL_Rect    visualGame::getRectangle(const string coords)
{
    int         x;
    int         y;
    SDL_Rect    obj;

    x = coords[0] - 97;
    y = atoi(coords.c_str() + 1);
    y = 8 - y;

    obj.h = _height / 10, obj.w = _width / 10;
    obj.x = _width / 10 + (_width / 10 * x), obj.y = _height / 10 + (_width / 10 * y);

    return (obj);
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

void    visualGame::loadBoard(const chessBoard *board, const int cx, const int cy)
{
    char        type;
    string      coords;
    string      color;
    SDL_Rect    obj;

    obj.h = _height, obj.w = _width, obj.x = 0, obj.y = 0;
    SDL_RenderCopy(_mainRenderer, _boardTexture, NULL, &obj);

    obj.h = _height / 10, obj.w = _width / 10;
    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            coords = string(1, "abcdefgh"[k]) + string(1, "87654321"[i]);
            type = board->getType(coords);
            color = board->getColor(coords);

            if (type != ' ')
            {
                if (coords != _droppedSourceCoords)
                    obj = getRectangle(coords);
                else
                    obj.x = cx - ((_width / 10) / 2), obj.y = cy - ((_height / 10) / 2);
                SDL_RenderCopy(_mainRenderer, getTexture(type, color), \
                    NULL, &obj);
            }
        }
    }
}

void    visualGame::displayGame(const chessBoard *board, const int cx, const int cy)
{
    SDL_RenderClear(_mainRenderer);
    loadBoard(board, cx, cy);
    loadText(board->getStateValue());
    SDL_RenderPresent(_mainRenderer);
}
