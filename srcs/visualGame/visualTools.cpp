#include "visualGame.hpp"

SDL_Texture *visualGame::getTexture(const char type, const string color) const
{
    if (color == "white")
    {
        if (type == 'c')
            return (_symbols.checkMateBlack.getTexture());

        if (type == 'K')
            return (_whiteTextures.king.getTexture());
        if (type == 'Q')
            return (_whiteTextures.queen.getTexture());
        if (type == 'R')
            return (_whiteTextures.rook.getTexture());
        if (type == 'B')
            return (_whiteTextures.bishop.getTexture());
        if (type == 'N')
            return (_whiteTextures.knight.getTexture());
        if (type == 'P')
            return (_whiteTextures.pawn.getTexture());
    }
    if (color == "black")
    {
        if (type == 'c')
            return (_symbols.checkMateWhite.getTexture());

        if (type == 'K')
            return (_blackTextures.king.getTexture());
        if (type == 'Q')
            return (_blackTextures.queen.getTexture());
        if (type == 'R')
            return (_blackTextures.rook.getTexture());
        if (type == 'B')
            return (_blackTextures.bishop.getTexture());
        if (type == 'N')
            return (_blackTextures.knight.getTexture());
        if (type == 'P')
            return (_blackTextures.pawn.getTexture());
    }
    return (nullptr);
}

SDL_Rect    visualGame::getRectangle(const string coords, const string type) const
{
    SDL_Rect    obj;

    if (type == "default")
    {
        obj.h = _height, obj.w = _width;
        obj.x = 0, obj.y = 0;
        return (obj);
    }

    if (type == "coords")
    {
        obj.h = _height / 22, obj.w = _width / 57;
        return (obj);
    }

    int x = coords[0] - 97;
    int y = atoi(coords.c_str() + 1) - 1;

    if (_aiSide != 0)
        y = 8 - (y + 1);
    else
        x = 7 - x;

    obj.x = _width / 14 + (_width / 10 * x), obj.y = _height / 10 + (_width / 10 * y);

    if (type == "promotion")
        obj.x = obj.x - _height / 47, obj.h = _height / 8, obj.w = _width / 7;
    else
        obj.h = _height / 10, obj.w = _width / 10;
    
    return (obj);
}

string  visualGame::getCoord(const int x, const int y) const
{
    int xZone;
    int yZone;

    if (x > 0 && y > 0 && x >= (_width / 14) && x <= ((_width / 10) * 9) + (_width / 14)
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
                xZone -= (_width / 34);

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
        return ("white");
    return ("black");
}

bool    visualGame::isPromotion(const string coord)
{
    if (_board->getType(_droppedSrc) == 'P')
    {
        if ((coord[1] == '8' && _droppedSrc[1] == '7')
            || (coord[1] == '1' && _droppedSrc[1] == '2'))
        {
            if (coord[0] == _droppedSrc[0] && _board->getType(coord) == ' ')
                return (true);
            if (coord[0] != _droppedSrc[0] && (coord[0] - _droppedSrc[0] != 1 || coord[0] - _droppedSrc[0] != -1)
                && _board->getType(coord) != ' ')
                return (true);
        }
    }
    return (false);
}

bool    visualGame::isAbovePromotion(const int x, const int y, SDL_Rect obj)
{
    if (x > obj.x && x < obj.x + (_width / 40)
        && y > obj.y + (_width / 40) && y <= obj.y + (_width / 40) + (_width / 20))
        return (true);

    if (x > obj.x + (_width / 9) && x < (obj.x + obj.w)
        && y > obj.y + (_width / 40) && y <= obj.y + (_width / 40) + (_width / 20))
        return (true);

    if (x > obj.x + (_width / 25) && x < (obj.x + obj.w) - (_width / 25)
        && y > obj.y + (_height / 16) && y < (obj.y + obj.h))
        return (true);

    return (false);
}
