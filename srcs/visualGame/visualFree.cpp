#include "visualGame.hpp"

visualGame::~visualGame()
{
    if (_board != nullptr)
        delete _board;

    if (_boardTexture != nullptr && _boardTexture != NULL)
        SDL_DestroyTexture(_boardTexture);

    if (_checkMateWhiteTexture != nullptr && _checkMateWhiteTexture != NULL)
        SDL_DestroyTexture(_checkMateWhiteTexture);
    if (_checkMateBlackTexture != nullptr && _checkMateBlackTexture != NULL)
        SDL_DestroyTexture(_checkMateBlackTexture);

    if (_arrowTexture != nullptr && _arrowTexture != NULL)
        SDL_DestroyTexture(_arrowTexture);

    if (_texts.blackToPlay != nullptr && _texts.blackToPlay != NULL)
        SDL_DestroyTexture(_texts.blackToPlay);
    if (_texts.blackWon != nullptr && _texts.blackWon != NULL)
        SDL_DestroyTexture(_texts.blackWon);

    if (_texts.whiteToPlay != nullptr && _texts.whiteToPlay != NULL)
        SDL_DestroyTexture(_texts.whiteToPlay);
    if (_texts.whiteWon != nullptr && _texts.whiteWon != NULL)
        SDL_DestroyTexture(_texts.whiteWon);

    if (_texts.draw != nullptr && _texts.draw != NULL)
        SDL_DestroyTexture(_texts.draw);

    if (_whiteTextures.pawn != nullptr && _whiteTextures.pawn != NULL)
        SDL_DestroyTexture(_whiteTextures.pawn);
    if (_whiteTextures.king != nullptr && _whiteTextures.king != NULL)
        SDL_DestroyTexture(_whiteTextures.king);
    if (_whiteTextures.queen != nullptr && _whiteTextures.queen != NULL)
        SDL_DestroyTexture(_whiteTextures.queen);
    if (_whiteTextures.bishop != nullptr && _whiteTextures.bishop != NULL)
        SDL_DestroyTexture(_whiteTextures.bishop);
    if (_whiteTextures.knight != nullptr && _whiteTextures.knight != NULL)
        SDL_DestroyTexture(_whiteTextures.knight);
    if (_whiteTextures.rook != nullptr && _whiteTextures.rook != NULL)
        SDL_DestroyTexture(_whiteTextures.rook);

    if (_blackTextures.pawn != nullptr && _blackTextures.pawn != NULL)
        SDL_DestroyTexture(_blackTextures.pawn);
    if (_blackTextures.king != nullptr && _blackTextures.king != NULL)
        SDL_DestroyTexture(_blackTextures.king);
    if (_blackTextures.queen != nullptr && _blackTextures.queen != NULL)
        SDL_DestroyTexture(_blackTextures.queen);
    if (_blackTextures.bishop != nullptr && _blackTextures.bishop != NULL)
        SDL_DestroyTexture(_blackTextures.bishop);
    if (_blackTextures.knight != nullptr && _blackTextures.knight != NULL)
        SDL_DestroyTexture(_blackTextures.knight);
    if (_blackTextures.rook != nullptr && _blackTextures.rook != NULL)
        SDL_DestroyTexture(_blackTextures.rook);

    if (_baseCheck != 0)
        SDL_FreeSurface(_baseSurface);

    if (_mainRenderer != nullptr && _mainRenderer != NULL)
        SDL_DestroyRenderer(_mainRenderer);
    if (_mainWindow != nullptr && _mainWindow != NULL)
        SDL_DestroyWindow(_mainWindow);

    if (_normalCursor != nullptr && _normalCursor != NULL)
        SDL_FreeCursor(_normalCursor);
    if (_playCursor != nullptr && _playCursor != NULL)
        SDL_FreeCursor(_playCursor);

    SDL_Quit();
}
