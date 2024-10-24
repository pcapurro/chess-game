#include "visualGame.hpp"

void    VisualGame::loadTexture(SDL_Texture *texture, const char *path)
{
    baseSurface = SDL_LoadBMP(path);
    if (!baseSurface)
        ;
    texture = SDL_CreateTextureFromSurface(mainRenderer, baseSurface);
    if (!texture)
        ;
    SDL_FreeSurface(baseSurface);
}

void    VisualGame::loadWhiteTextures(void)
{
    loadTexture(whiteTextures.king, "./materials/white/king.bmp");
    loadTexture(whiteTextures.queen, "./materials/white/queen.bmp");

    loadTexture(whiteTextures.knight, "./materials/white/knight.bmp");
    loadTexture(whiteTextures.bishop, "./materials/white/bishop.bmp");
    loadTexture(whiteTextures.rook, "./materials/white/rook.bmp");

    loadTexture(whiteTextures.pawn, "./materials/white/pawn.bmp");
}

void    VisualGame::loadBlackTextures(void)
{
    loadTexture(blackTextures.king, "./materials/black/king.bmp");
    loadTexture(blackTextures.queen, "./materials/black/queen.bmp");

    loadTexture(blackTextures.knight, "./materials/black/knight.bmp");
    loadTexture(blackTextures.bishop, "./materials/black/bishop.bmp");
    loadTexture(blackTextures.rook, "./materials/black/rook.bmp");

    loadTexture(blackTextures.pawn, "./materials/black/pawn.bmp");
}

void    VisualGame::loadTextures(void)
{
    baseSurface = SDL_LoadBMP("./materials/board.bmp");
    if (baseSurface)
        ;
    boardTexture = SDL_CreateTextureFromSurface(mainRenderer, baseSurface);
    if (boardTexture)
        ;
    SDL_FreeSurface(baseSurface);

    loadWhiteTextures();
    loadBlackTextures();
}
