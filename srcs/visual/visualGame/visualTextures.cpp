#include "visualGame.hpp"

void    visualGame::loadTexture(const char type, const char color, const char *path)
{
    _baseSurface = SDL_LoadBMP(path);

    if (type == 'K' && color == 'w')
        _whiteTextures.king = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (type == 'Q' && color == 'w')
        _whiteTextures.queen = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (type == 'N' && color == 'w')
        _whiteTextures.knight = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (type == 'B' && color == 'w')
        _whiteTextures.bishop = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (type == 'R' && color == 'w')
        _whiteTextures.rook = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (type == 'P' && color == 'w')
        _whiteTextures.pawn = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);

    if (type == 'K' && color == 'b')
        _blackTextures.king = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (type == 'Q' && color == 'b')
        _blackTextures.queen = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (type == 'N' && color == 'b')
        _blackTextures.knight = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (type == 'B' && color == 'b')
        _blackTextures.bishop = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (type == 'R' && color == 'b')
        _blackTextures.rook = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (type == 'P' && color == 'b')
        _blackTextures.pawn = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);

    SDL_FreeSurface(_baseSurface);
}

void    visualGame::loadWhiteTextures(void)
{
    loadTexture('K', 'w', "./materials/white/king.bmp");
    loadTexture('Q', 'w', "./materials/white/queen.bmp");

    loadTexture('N', 'w', "./materials/white/knight.bmp");
    loadTexture('B', 'w', "./materials/white/bishop.bmp");
    loadTexture('R', 'w', "./materials/white/rook.bmp");

    loadTexture('P', 'w', "./materials/white/pawn.bmp");
}

void    visualGame::loadBlackTextures(void)
{
    loadTexture('K', 'b', "./materials/black/king.bmp");
    loadTexture('Q', 'b', "./materials/black/queen.bmp");

    loadTexture('N', 'b', "./materials/black/knight.bmp");
    loadTexture('B', 'b', "./materials/black/bishop.bmp");
    loadTexture('R', 'b', "./materials/black/rook.bmp");

    loadTexture('P', 'b', "./materials/black/pawn.bmp");
}

void    visualGame::loadTextures(void)
{
    _baseSurface = SDL_LoadBMP("./materials/board.bmp");
    _boardTexture = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    SDL_FreeSurface(_baseSurface);

    loadWhiteTextures();
    loadBlackTextures();
}
