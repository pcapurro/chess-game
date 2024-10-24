#include "visualGame.hpp"

SDL_Texture *VisualGame::getTexture(const char type, const string color) const
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

SDL_Rect    VisualGame::getRectangle(const string coords)
{
    int         x;
    int         y;
    SDL_Rect    obj;

    x = coords[0] - 97;
    y = atoi(coords.c_str() + 1);

    obj.h = _height / 9, obj.w = _width / 9;
    obj.x = _width / 10 + (_width / 10 * x), obj.y = _height / 10 + (_width / 10 * y);

    return (obj);
}

void    VisualGame::loadBoard(const chessBoard *board)
{
    char        type;
    string      coords;
    string      color;
    SDL_Rect    obj;

    SDL_RenderClear(_mainRenderer);
    SDL_RenderCopy(_mainRenderer, _boardTexture, NULL, NULL);

    for (int i = 9; i != 1; i--)
    {
        for (int k = 0; k != 8; k++)
        {
            coords = "abcdefgh"[k] + to_string(i - 1);
            type = board->getType(coords);
            color = board->getColor(coords);

            if (type != ' ')
            {
                obj = getRectangle(coords);
                SDL_RenderCopy(_mainRenderer, getTexture(type, color), \
                    NULL, &obj);
            }
        }
    }
}

void    VisualGame::displayFrame(void)
{
    SDL_RenderPresent(_mainRenderer);
    SDL_Delay(10000);
}
