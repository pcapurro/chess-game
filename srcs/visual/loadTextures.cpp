#include "../../include/shellChessVisual.hpp"

int loadTexture(t_game *mainStr, SDL_Texture *texture, const char *path)
{
    mainStr->baseSurface = SDL_LoadBMP(path);
    if (!mainStr->baseSurface)
        return (1);
    texture = SDL_CreateTextureFromSurface(mainStr->mainRenderer, mainStr->baseSurface);
    if (!texture)
        return (1);
    SDL_FreeSurface(mainStr->baseSurface);

    return (0);
}

int loadWhiteTextures(t_game *mainStr)
{
    if (loadTexture(mainStr, mainStr->whiteTextures.king, "./materials/white/king.bmp") != 0)
        return (1);
    if (loadTexture(mainStr, mainStr->whiteTextures.queen, "./materials/white/queen.bmp") != 0)
        return (1);

    if (loadTexture(mainStr, mainStr->whiteTextures.rook, "./materials/white/rook.bmp") != 0)
        return (1);
    if (loadTexture(mainStr, mainStr->whiteTextures.bishop, "./materials/white/bishop.bmp") != 0)
        return (1);
    if (loadTexture(mainStr, mainStr->whiteTextures.knight, "./materials/white/knight.bmp") != 0)
        return (1);

    if (loadTexture(mainStr, mainStr->whiteTextures.pawn, "./materials/white/pawn.bmp") != 0)
        return (1);

    return (0);
}

int loadBlackTextures(t_game *mainStr)
{
    if (loadTexture(mainStr, mainStr->blackTextures.king, "./materials/black/king.bmp") != 0)
        return (1);
    if (loadTexture(mainStr, mainStr->blackTextures.queen, "./materials/black/queen.bmp") != 0)
        return (1);

    if (loadTexture(mainStr, mainStr->blackTextures.rook, "./materials/black/rook.bmp") != 0)
        return (1);
    if (loadTexture(mainStr, mainStr->blackTextures.bishop, "./materials/black/bishop.bmp") != 0)
        return (1);
    if (loadTexture(mainStr, mainStr->blackTextures.knight, "./materials/black/knight.bmp") != 0)
        return (1);

    if (loadTexture(mainStr, mainStr->blackTextures.pawn, "./materials/black/pawn.bmp") != 0)
        return (1);

    return (0);
}

void    *loadTextures(t_game *mainStr)
{
    mainStr->baseSurface = SDL_LoadBMP("./materials/board.bmp");
    if (!mainStr->baseSurface)
        return (nullptr);
    mainStr->boardTexture = SDL_CreateTextureFromSurface(mainStr->mainRenderer, mainStr->baseSurface);
    if (!mainStr->boardTexture)
        return (nullptr);
    SDL_FreeSurface(mainStr->baseSurface);

    if (loadWhiteTextures(mainStr) != 0)
        return (nullptr);

    if (loadBlackTextures(mainStr) != 0)
        return (nullptr);

    return (mainStr);
}
