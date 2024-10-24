#include "visualGame.hpp"

VisualGame::~VisualGame()
{
    if (whiteTextures.pawn != nullptr)
        SDL_DestroyTexture(whiteTextures.pawn);
    if (whiteTextures.king != nullptr)
        SDL_DestroyTexture(whiteTextures.king);
    if (whiteTextures.queen != nullptr)
        SDL_DestroyTexture(whiteTextures.queen);
    if (whiteTextures.bishop != nullptr)
        SDL_DestroyTexture(whiteTextures.bishop);
    if (whiteTextures.knight != nullptr)
        SDL_DestroyTexture(whiteTextures.knight);
    if (whiteTextures.rook != nullptr)
        SDL_DestroyTexture(whiteTextures.rook);

    if (blackTextures.pawn != nullptr)
        SDL_DestroyTexture(blackTextures.pawn);
    if (blackTextures.king != nullptr)
        SDL_DestroyTexture(blackTextures.king);
    if (blackTextures.queen != nullptr)
        SDL_DestroyTexture(blackTextures.queen);
    if (blackTextures.bishop != nullptr)
        SDL_DestroyTexture(blackTextures.bishop);
    if (blackTextures.knight != nullptr)
        SDL_DestroyTexture(blackTextures.knight);
    if (blackTextures.rook != nullptr)
        SDL_DestroyTexture(blackTextures.rook);

    if (mainWindow != nullptr)
        SDL_DestroyWindow(mainWindow);
    if (mainRenderer != nullptr)
        SDL_DestroyRenderer(mainRenderer);

    SDL_Quit();
}