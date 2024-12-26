#include "visualGame.hpp"

visualGame::~visualGame()
{
    if (_board != nullptr)
        delete _board;

    if (_boardTexture != nullptr && _boardTexture != NULL)
        SDL_DestroyTexture(_boardTexture);

    if (_symbols.checkMateWhite != nullptr && _symbols.checkMateWhite != NULL)
        SDL_DestroyTexture(_symbols.checkMateWhite);
    if (_symbols.checkMateBlack != nullptr && _symbols.checkMateBlack != NULL)
        SDL_DestroyTexture(_symbols.checkMateBlack);

    if (_letters.a != nullptr && _letters.a != NULL)
        SDL_DestroyTexture(_letters.a);
    if (_letters.b != nullptr && _letters.b != NULL)
        SDL_DestroyTexture(_letters.b);
    if (_letters.c != nullptr && _letters.c != NULL)
        SDL_DestroyTexture(_letters.c);
    if (_letters.d != nullptr && _letters.d != NULL)
        SDL_DestroyTexture(_letters.d);

    if (_letters.e != nullptr && _letters.e != NULL)
        SDL_DestroyTexture(_letters.e);
    if (_letters.f != nullptr && _letters.f != NULL)
        SDL_DestroyTexture(_letters.f);
    if (_letters.g != nullptr && _letters.g != NULL)
        SDL_DestroyTexture(_letters.g);
    if (_letters.h != nullptr && _letters.h != NULL)
        SDL_DestroyTexture(_letters.h);

    if (_numbers.one != nullptr && _numbers.one != NULL)
        SDL_DestroyTexture(_numbers.one);
    if (_numbers.two != nullptr && _numbers.two != NULL)
        SDL_DestroyTexture(_numbers.two);
    if (_numbers.three != nullptr && _numbers.three != NULL)
        SDL_DestroyTexture(_numbers.three);
    if (_numbers.four != nullptr && _numbers.four != NULL)
        SDL_DestroyTexture(_numbers.four);

    if (_numbers.five != nullptr && _numbers.five != NULL)
        SDL_DestroyTexture(_numbers.five);
    if (_numbers.six != nullptr && _numbers.six != NULL)
        SDL_DestroyTexture(_numbers.six);
    if (_numbers.seven != nullptr && _numbers.seven != NULL)
        SDL_DestroyTexture(_numbers.seven);
    if (_numbers.eight != nullptr && _numbers.eight != NULL)
        SDL_DestroyTexture(_numbers.eight);

    if (_symbols.plus != nullptr && _symbols.plus != NULL)
        SDL_DestroyTexture(_symbols.plus);
    if (_symbols.moins != nullptr && _symbols.moins != NULL)
        SDL_DestroyTexture(_symbols.moins);

    if (_arrow != nullptr && _arrow != NULL)
        SDL_DestroyTexture(_arrow);

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
