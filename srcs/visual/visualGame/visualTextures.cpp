#include "visualGame.hpp"

void    VisualGame::loadTexture(SDL_Texture *texture, const char *path)
{
    _baseSurface = SDL_LoadBMP(path);
    texture = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    SDL_FreeSurface(_baseSurface);
}

void    VisualGame::loadWhiteTextures(void)
{
    loadTexture(_whiteTextures.king, "./materials/white/king.bmp");
    loadTexture(_whiteTextures.queen, "./materials/white/queen.bmp");

    loadTexture(_whiteTextures.knight, "./materials/white/knight.bmp");
    loadTexture(_whiteTextures.bishop, "./materials/white/bishop.bmp");
    loadTexture(_whiteTextures.rook, "./materials/white/rook.bmp");

    loadTexture(_whiteTextures.pawn, "./materials/white/pawn.bmp");
}

void    VisualGame::loadBlackTextures(void)
{
    loadTexture(_blackTextures.king, "./materials/black/king.bmp");
    loadTexture(_blackTextures.queen, "./materials/black/queen.bmp");

    loadTexture(_blackTextures.knight, "./materials/black/knight.bmp");
    loadTexture(_blackTextures.bishop, "./materials/black/bishop.bmp");
    loadTexture(_blackTextures.rook, "./materials/black/rook.bmp");

    loadTexture(_blackTextures.pawn, "./materials/black/pawn.bmp");
}

void    VisualGame::loadTextures(void)
{
    _baseSurface = SDL_LoadBMP("./materials/board.bmp");
    _boardTexture = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    SDL_FreeSurface(_baseSurface);

    loadWhiteTextures();
    loadBlackTextures();
}
