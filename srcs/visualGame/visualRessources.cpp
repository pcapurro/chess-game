#include "visualGame.hpp"

void    visualGame::loadTexts(void)
{
    if (_error == true)
        return ;

    int value = 0;

    value += _textures->texts.blackToPlay.load(_mainRenderer, "./materials/texts/black-to-play.bmp");
    value += _textures->texts.whiteToPlay.load(_mainRenderer, "./materials/texts/white-to-play.bmp");

    value += _textures->texts.whiteWon.load(_mainRenderer, "./materials/texts/white-won.bmp");
    value += _textures->texts.blackWon.load(_mainRenderer, "./materials/texts/black-won.bmp");

    value += _textures->texts.draw.load(_mainRenderer, "./materials/texts/draw.bmp");

    if (value != 0)
        _error = true;
}

void    visualGame::loadLetters(void)
{
    if (_error == true)
        return ;

    int value = 0;

    value += _textures->letters.a.load(_mainRenderer, "./materials/letters/a.bmp");
    value += _textures->letters.b.load(_mainRenderer, "./materials/letters/b.bmp");
    value += _textures->letters.c.load(_mainRenderer, "./materials/letters/c.bmp");
    value += _textures->letters.d.load(_mainRenderer, "./materials/letters/d.bmp");

    value += _textures->letters.e.load(_mainRenderer, "./materials/letters/e.bmp");
    value += _textures->letters.f.load(_mainRenderer, "./materials/letters/f.bmp");
    value += _textures->letters.g.load(_mainRenderer, "./materials/letters/g.bmp");
    value += _textures->letters.h.load(_mainRenderer, "./materials/letters/h.bmp");


    if (value != 0)
        _error = true;
}

void    visualGame::loadNumbers(void)
{
    if (_error == true)
        return ;

    int value = 0;

    value += _textures->numbers.one.load(_mainRenderer, "./materials/numbers/1.bmp");
    value += _textures->numbers.two.load(_mainRenderer, "./materials/numbers/2.bmp");
    value += _textures->numbers.three.load(_mainRenderer, "./materials/numbers/3.bmp");
    value += _textures->numbers.four.load(_mainRenderer, "./materials/numbers/4.bmp");

    value += _textures->numbers.five.load(_mainRenderer, "./materials/numbers/5.bmp");
    value += _textures->numbers.six.load(_mainRenderer, "./materials/numbers/6.bmp");
    value += _textures->numbers.seven.load(_mainRenderer, "./materials/numbers/7.bmp");
    value += _textures->numbers.eight.load(_mainRenderer, "./materials/numbers/8.bmp");

    if (value != 0)
        _error = true;
}

void    visualGame::loadSymbols(void)
{
    if (_error == true)
        return ;

    int value = 0;

    value += _textures->symbols.plus.load(_mainRenderer, "./materials/symbols/plus.bmp");
    value += _textures->symbols.moins.load(_mainRenderer, "./materials/symbols/moins.bmp");

    if (value != 0)
        _error = true;
}

void    visualGame::loadWhiteTextures(void)
{
    if (_error == true)
        return ;

    int value = 0;

    value += _textures->whiteTextures.king.load(_mainRenderer, "./materials/images/white/king.bmp");
    value += _textures->whiteTextures.queen.load(_mainRenderer, "./materials/images/white/queen.bmp");

    value += _textures->whiteTextures.knight.load(_mainRenderer, "./materials/images/white/knight.bmp");
    value += _textures->whiteTextures.bishop.load(_mainRenderer, "./materials/images/white/bishop.bmp");
    value += _textures->whiteTextures.rook.load(_mainRenderer, "./materials/images/white/rook.bmp");

    value += _textures->whiteTextures.pawn.load(_mainRenderer, "./materials/images/white/pawn.bmp");

    if (value != 0)
        _error = true;
}

void    visualGame::loadBlackTextures(void)
{
    if (_error == true)
        return ;

    int value = 0;

    value += _textures->blackTextures.king.load(_mainRenderer, "./materials/images/black/king.bmp");
    value += _textures->blackTextures.queen.load(_mainRenderer, "./materials/images/black/queen.bmp");

    value += _textures->blackTextures.knight.load(_mainRenderer, "./materials/images/black/knight.bmp");
    value += _textures->blackTextures.bishop.load(_mainRenderer, "./materials/images/black/bishop.bmp");
    value += _textures->blackTextures.rook.load(_mainRenderer, "./materials/images/black/rook.bmp");

    value += _textures->blackTextures.pawn.load(_mainRenderer, "./materials/images/black/pawn.bmp");

    if (value != 0)
        _error = true;
}

void    visualGame::loadBoardTextures(void)
{
    if (_error == true)
        return ;

    int value = 0;

    value += _textures->boardTexture.load(_mainRenderer, "./materials/images/board.bmp");

    value += _textures->symbols.checkMateWhite.load(_mainRenderer, "./materials/symbols/checkmate-white.bmp");
    value += _textures->symbols.checkMateBlack.load(_mainRenderer, "./materials/symbols/checkmate-black.bmp");

    value += _textures->promotion.load(_mainRenderer, "./materials/images/promotion.bmp");

    if (value != 0)
        _error = true;
}

void    visualGame::loadTextures(void)
{
    loadTexts();

    loadLetters();
    loadNumbers();
    loadSymbols();

    loadBoardTextures();
    loadWhiteTextures();
    loadBlackTextures();
}
