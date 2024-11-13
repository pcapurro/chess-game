#include "visualGame.hpp"

SDL_Texture *visualGame::getTexture(const char type, const string color) const
{
    if (color == "white")
    {
        if (type == 'c')
            return (_checkMateBlackTexture);

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
        if (type == 'c')
            return (_checkMateWhiteTexture);

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

SDL_Rect    visualGame::getRectangle(const string coords, const float fx, const float fy) const
{
    SDL_Rect    obj;

    if (coords == "default")
        obj.h = _height, obj.w = _width, obj.x = 0, obj.y = 0;
    else
    {
        float   x;
        float   y;

        x = coords[0] - 97;
        y = atoi(coords.c_str() + 1) - 1;

        if (_aiSide != 0)
            y = 8 - (y + 1);
        else
            x = 7 - x;
    
        obj.h = _height / 10, obj.w = _width / 10;
        obj.x = _width / 10 + (_width / 10 * x), obj.y = _height / 10 + (_width / 10 * y);

        obj.x = obj.x - fx, obj.y = obj.y - fy;
    }
    
    return (obj);
}

string  visualGame::getCoord(const int x, const int y) const
{
    int xZone;
    int yZone;

    if (x > 0 && y > 0 && x >= _width / 10 && x <= _width / 10 * 9
        && y >= (_height / 10) && y <= (_height / 10 * 9))
    {
        for (int i = 0; i != 8; i++)
        {
            if (_aiSide == 0)
                yZone = (_height / 10) * (i + 1);
            else
                yZone = (_height / 10) * (8 - i);

            for (int k = 0; k != 8; k++)
            {
                if (_aiSide == 0)
                    xZone = (_width / 10 ) * (8 - k);
                else
                    xZone = (_width / 10 ) * (k + 1);

                if (x >= xZone && x <= xZone + (_width / 10 ) && y >= yZone && y <= yZone + (_height / 10 ))
                    return (string(1, "abcdefgh"[k]) + string(1, "12345678"[i]));
            }
        }
    }
    return ("none");
}

string  visualGame::getKingCoords(const string color)
{
    string      coords;

    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            coords = string(1, "hgfedcba"[k]) + string(1, "87654321"[i]);
            if (_board->getType(coords) == 'K' && _board->getColor(coords) == color)
                return (coords);
        }
    }
    return (coords);
}

string  visualGame::getTurnColor(void) const
{
    if (_turn % 2 == 0)
        return (string("white"));
    return (string("black"));
}
