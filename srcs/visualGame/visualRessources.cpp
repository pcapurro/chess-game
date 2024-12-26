#include "visualGame.hpp"

void    visualGame::loadTexts(void)
{
    if (_error == true)
        return ;

    if (_texts.blackToPlay.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/texts/black-to-play.bmp") == nullptr)
        { _error = true; return; }

    if (_texts.whiteToPlay.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/texts/white-to-play.bmp") == nullptr)
        { _error = true; return; }

    if (_texts.whiteWon.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/texts/white-won.bmp") == nullptr)
        { _error = true; return; }

    if (_texts.blackWon.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/texts/black-won.bmp") == nullptr)
        { _error = true; return; }

    if (_texts.draw.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/texts/draw.bmp") == nullptr)
        { _error = true; return; }
}

void    visualGame::loadLetters(void)
{
    if (_error == true)
        return ;

    if (_letters.a.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/letters/a.bmp") == nullptr)
        { _error = true; return; }

    if (_letters.b.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/letters/b.bmp") == nullptr)
        { _error = true; return; }

    if (_letters.c.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/letters/c.bmp") == nullptr)
        { _error = true; return; }

    if (_letters.d.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/letters/d.bmp") == nullptr)
        { _error = true; return; }

    if (_letters.e.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/letters/e.bmp") == nullptr)
        { _error = true; return; }

    if (_letters.f.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/letters/f.bmp") == nullptr)
        { _error = true; return; }

    if (_letters.g.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/letters/g.bmp") == nullptr)
        { _error = true; return; }

    if (_letters.h.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/letters/h.bmp") == nullptr)
        { _error = true; return; }
}

void    visualGame::loadNumbers(void)
{
    if (_error == true)
        return ;

    if (_numbers.one.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/numbers/1.bmp") == nullptr)
        { _error = true; return; }

    if (_numbers.two.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/numbers/2.bmp") == nullptr)
        { _error = true; return; }

    if (_numbers.three.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/numbers/3.bmp") == nullptr)
        { _error = true; return; }

    if (_numbers.four.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/numbers/4.bmp") == nullptr)
        { _error = true; return; }

    if (_numbers.five.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/numbers/5.bmp") == nullptr)
        { _error = true; return; }

    if (_numbers.six.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/numbers/6.bmp") == nullptr)
        { _error = true; return; }

    if (_numbers.seven.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/numbers/7.bmp") == nullptr)
        { _error = true; return; }

    if (_numbers.eight.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/numbers/8.bmp") == nullptr)
        { _error = true; return; }
}

void    visualGame::loadSymbols(void)
{
    if (_error == true)
        return ;

    if (_symbols.plus.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/symbols/plus.bmp") == nullptr)
        { _error = true; return; }

    if (_symbols.moins.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/symbols/moins.bmp") == nullptr)
        { _error = true; return; }
}

void    visualGame::loadWhiteTextures(void)
{
    if (_error == true)
        return ;

    if (_whiteTextures.king.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/images/white/king.bmp") == nullptr)
        { _error = true; return; }
    if (_whiteTextures.queen.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/images/white/queen.bmp") == nullptr)
        { _error = true; return; }

    if (_whiteTextures.knight.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/images/white/knight.bmp") == nullptr)
        { _error = true; return; }
    if (_whiteTextures.bishop.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/images/white/bishop.bmp") == nullptr)
        { _error = true; return; }
    if (_whiteTextures.rook.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/images/white/rook.bmp") == nullptr)
        { _error = true; return; }

    if (_whiteTextures.pawn.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/images/white/pawn.bmp") == nullptr)
        { _error = true; return; }
}

void    visualGame::loadBlackTextures(void)
{
    if (_error == true)
        return ;

    if (_blackTextures.king.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/images/black/king.bmp") == nullptr)
        { _error = true; return; }
    if (_blackTextures.queen.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/images/black/queen.bmp") == nullptr)
        { _error = true; return; }

    if (_blackTextures.knight.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/images/black/knight.bmp") == nullptr)
        { _error = true; return; }
    if (_blackTextures.bishop.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/images/black/bishop.bmp") == nullptr)
        { _error = true; return; }
    if (_blackTextures.rook.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/images/black/rook.bmp") == nullptr)
        { _error = true; return; }

    if (_blackTextures.pawn.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/images/black/pawn.bmp") == nullptr)
        { _error = true; return; }
}

void    visualGame::loadBoardTextures(void)
{
    if (_error == true)
        return ;

    if (_boardTexture.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/images/board.bmp") == nullptr)
        { _error = true; return; }

    if (_symbols.checkMateWhite.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/symbols/checkmate-white.bmp") == nullptr)
        { _error = true; return; }

    if (_symbols.checkMateBlack.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/symbols/checkmate-black.bmp") == nullptr)
        { _error = true; return; }

    if (_promotion.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/images/promotion.bmp") == nullptr)
        { _error = true; return; }
}

void    visualGame::loadArrowTexture(void)
{
    if (_error == true)
        return ;

    if (_arrow.load(_mainRenderer, _baseSurface, _baseCheck, "./materials/images/arrow.bmp") == nullptr)
        { _error = true; return; }
}

void    visualGame::loadTextures(void)
{
    loadTexts();

    loadLetters();
    loadNumbers();
    loadSymbols();

    loadBoardTextures();
    loadArrowTexture();

    loadWhiteTextures();
    loadBlackTextures();
}
