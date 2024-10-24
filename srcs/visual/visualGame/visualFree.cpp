#include "visualGame.hpp"

VisualGame::~VisualGame()
{
    if (_whiteTextures.pawn != nullptr)
        SDL_DestroyTexture(_whiteTextures.pawn);
    if (_whiteTextures.king != nullptr)
        SDL_DestroyTexture(_whiteTextures.king);
    if (_whiteTextures.queen != nullptr)
        SDL_DestroyTexture(_whiteTextures.queen);
    if (_whiteTextures.bishop != nullptr)
        SDL_DestroyTexture(_whiteTextures.bishop);
    if (_whiteTextures.knight != nullptr)
        SDL_DestroyTexture(_whiteTextures.knight);
    if (_whiteTextures.rook != nullptr)
        SDL_DestroyTexture(_whiteTextures.rook);

    if (_blackTextures.pawn != nullptr)
        SDL_DestroyTexture(_blackTextures.pawn);
    if (_blackTextures.king != nullptr)
        SDL_DestroyTexture(_blackTextures.king);
    if (_blackTextures.queen != nullptr)
        SDL_DestroyTexture(_blackTextures.queen);
    if (_blackTextures.bishop != nullptr)
        SDL_DestroyTexture(_blackTextures.bishop);
    if (_blackTextures.knight != nullptr)
        SDL_DestroyTexture(_blackTextures.knight);
    if (_blackTextures.rook != nullptr)
        SDL_DestroyTexture(_blackTextures.rook);

    if (_mainWindow != nullptr)
        SDL_DestroyWindow(_mainWindow);
    if (_mainRenderer != nullptr)
        SDL_DestroyRenderer(_mainRenderer);

    SDL_Quit();
}