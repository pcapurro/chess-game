#include "visualGame.hpp"

SDL_Texture *visualGame::getTexture(const char type, const string color) const
{
    if (color == "white")
    {
        if (type == 'c')
            return (_textures->symbols.checkMateBlack.getTexture());

        if (type == 'K')
            return (_textures->whiteTextures.king.getTexture());
        if (type == 'Q')
            return (_textures->whiteTextures.queen.getTexture());
        if (type == 'R')
            return (_textures->whiteTextures.rook.getTexture());
        if (type == 'B')
            return (_textures->whiteTextures.bishop.getTexture());
        if (type == 'N')
            return (_textures->whiteTextures.knight.getTexture());
        if (type == 'P')
            return (_textures->whiteTextures.pawn.getTexture());
    }
    if (color == "black")
    {
        if (type == 'c')
            return (_textures->symbols.checkMateWhite.getTexture());

        if (type == 'K')
            return (_textures->blackTextures.king.getTexture());
        if (type == 'Q')
            return (_textures->blackTextures.queen.getTexture());
        if (type == 'R')
            return (_textures->blackTextures.rook.getTexture());
        if (type == 'B')
            return (_textures->blackTextures.bishop.getTexture());
        if (type == 'N')
            return (_textures->blackTextures.knight.getTexture());
        if (type == 'P')
            return (_textures->blackTextures.pawn.getTexture());
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

    int x = coords[0] - 97;
    int y = atoi(coords.c_str() + 1) - 1;

    if (_aiSide != 0)
        y = 8 - (y + 1);
    else
        x = 7 - x;

    obj.x = 105 + (80 * x), obj.y = 80 + (80 * y);

    if (type == "coordsl" || type == "coordsn")
    {
        obj.w = 14, obj.h = 35;

        if (type == "coordsl")
        {
            obj.x = obj.x + 40 - 7;
            obj.y = _height - 75;
        }
        else
            obj.x = 75, obj.y = obj.y + 40 - (obj.h / 2);
        return (obj);
    }

    if (type == "promotion")
        obj.x = obj.x - 17, obj.h = 100, obj.w = 114;
    else
        obj.h = 80, obj.w = 80;

    return (obj);
}

string  visualGame::getCoord(const int x, const int y) const
{
    int xZone;
    int yZone;

    cout << x << " ; " << y << endl;

    if (x >= 105 && x <= 745 && y >= 80 && y <= 720)
    {
        for (int i = 0; i != 8; i++)
        {
            if (_aiSide == 0)
                yZone = 80 * (i + 1);
            else
                yZone = 80 * (8 - i);

            for (int k = 0; k != 8; k++)
            {
                if (_aiSide == 0)
                    xZone = 80 * (8 - k);
                else
                    xZone = 80 * (k + 1);

                if (x >= xZone && x <= xZone + 105 && y >= yZone && y <= yZone + 105)
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
    if (x > obj.x && x < obj.x + 20
        && y > obj.y + 20 && y <= obj.y + 20 + 40)
        return (true);

    if (x > obj.x + 88 && x < (obj.x + obj.w)
        && y > obj.y + 20 && y <= obj.y + 20 + 40)
        return (true);

    if (x > obj.x + 32 && x < (obj.x + obj.w) - 32
        && y > obj.y + 50 && y < (obj.y + obj.h))
        return (true);

    return (false);
}
