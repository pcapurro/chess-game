#include "visualGame.hpp"

void    visualGame::loadTexts(void)
{
    if (_error == true)
        return ;

    if (_textures->texts.blackToPlay.load(_mainRenderer, "./materials/texts/black-to-play.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->texts.whiteToPlay.load(_mainRenderer, "./materials/texts/white-to-play.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->texts.whiteWon.load(_mainRenderer, "./materials/texts/white-won.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->texts.blackWon.load(_mainRenderer, "./materials/texts/black-won.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->texts.draw.load(_mainRenderer, "./materials/texts/draw.bmp") == nullptr)
        { _error = true; return; }
}

void    visualGame::loadLetters(void)
{
    if (_error == true)
        return ;

    if (_textures->letters.a.load(_mainRenderer, "./materials/letters/a.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->letters.b.load(_mainRenderer, "./materials/letters/b.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->letters.c.load(_mainRenderer, "./materials/letters/c.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->letters.d.load(_mainRenderer, "./materials/letters/d.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->letters.e.load(_mainRenderer, "./materials/letters/e.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->letters.f.load(_mainRenderer, "./materials/letters/f.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->letters.g.load(_mainRenderer, "./materials/letters/g.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->letters.h.load(_mainRenderer, "./materials/letters/h.bmp") == nullptr)
        { _error = true; return; }
}

void    visualGame::loadNumbers(void)
{
    if (_error == true)
        return ;

    if (_textures->numbers.one.load(_mainRenderer, "./materials/numbers/1.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->numbers.two.load(_mainRenderer, "./materials/numbers/2.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->numbers.three.load(_mainRenderer, "./materials/numbers/3.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->numbers.four.load(_mainRenderer, "./materials/numbers/4.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->numbers.five.load(_mainRenderer, "./materials/numbers/5.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->numbers.six.load(_mainRenderer, "./materials/numbers/6.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->numbers.seven.load(_mainRenderer, "./materials/numbers/7.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->numbers.eight.load(_mainRenderer, "./materials/numbers/8.bmp") == nullptr)
        { _error = true; return; }
}

void    visualGame::loadSymbols(void)
{
    if (_error == true)
        return ;

    if (_textures->symbols.plus.load(_mainRenderer, "./materials/symbols/plus.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->symbols.moins.load(_mainRenderer, "./materials/symbols/moins.bmp") == nullptr)
        { _error = true; return; }
}

void    visualGame::loadWhiteTextures(void)
{
    if (_error == true)
        return ;

    if (_textures->whiteTextures.king.load(_mainRenderer, "./materials/images/white/king.bmp") == nullptr)
        { _error = true; return; }
    if (_textures->whiteTextures.queen.load(_mainRenderer, "./materials/images/white/queen.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->whiteTextures.knight.load(_mainRenderer, "./materials/images/white/knight.bmp") == nullptr)
        { _error = true; return; }
    if (_textures->whiteTextures.bishop.load(_mainRenderer, "./materials/images/white/bishop.bmp") == nullptr)
        { _error = true; return; }
    if (_textures->whiteTextures.rook.load(_mainRenderer, "./materials/images/white/rook.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->whiteTextures.pawn.load(_mainRenderer, "./materials/images/white/pawn.bmp") == nullptr)
        { _error = true; return; }
}

void    visualGame::loadBlackTextures(void)
{
    if (_error == true)
        return ;

    if (_textures->blackTextures.king.load(_mainRenderer, "./materials/images/black/king.bmp") == nullptr)
        { _error = true; return; }
    if (_textures->blackTextures.queen.load(_mainRenderer, "./materials/images/black/queen.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->blackTextures.knight.load(_mainRenderer, "./materials/images/black/knight.bmp") == nullptr)
        { _error = true; return; }
    if (_textures->blackTextures.bishop.load(_mainRenderer, "./materials/images/black/bishop.bmp") == nullptr)
        { _error = true; return; }
    if (_textures->blackTextures.rook.load(_mainRenderer, "./materials/images/black/rook.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->blackTextures.pawn.load(_mainRenderer, "./materials/images/black/pawn.bmp") == nullptr)
        { _error = true; return; }
}

void    visualGame::loadBoardTextures(void)
{
    if (_error == true)
        return ;

    if (_textures->boardTexture.load(_mainRenderer, "./materials/images/board.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->symbols.checkMateWhite.load(_mainRenderer, "./materials/symbols/checkmate-white.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->symbols.checkMateBlack.load(_mainRenderer, "./materials/symbols/checkmate-black.bmp") == nullptr)
        { _error = true; return; }

    if (_textures->promotion.load(_mainRenderer, "./materials/images/promotion.bmp") == nullptr)
        { _error = true; return; }
}

void    visualGame::loadArrowTexture(void)
{
    if (_error == true)
        return ;

    if (_textures->arrow.load(_mainRenderer, "./materials/images/arrow.bmp") == nullptr)
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
