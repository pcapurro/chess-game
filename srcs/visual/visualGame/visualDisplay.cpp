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
    SDL_Rect    obj;
}

void    VisualGame::loadBoard(const chessBoard *board)
{
    char        type;
    string      coords;
    string      color;

    SDL_RenderClear(_mainRenderer);
    SDL_RenderCopy(_mainRenderer, _boardTexture, NULL, NULL);

    for (int i = 8; i != -1; i--)
    {
        for (int k = 0; k != 8; k++)
        {
            coords = "abcdefgh"[k] + to_string(i - 1);
            type = board->getType(coords);
            color = board->getColor(coords);

            if (type != ' ')
                SDL_RenderCopy(_mainRenderer, getTexture(type, color), \
                    NULL, &getRectangle(coords));
        }
    }
}

void    VisualGame::displayFrame(void)
{
    SDL_RenderPresent(_mainRenderer);
    SDL_Delay(10000);
}
