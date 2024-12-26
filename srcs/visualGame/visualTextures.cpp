#include "visualGame.hpp"

void    visualGame::loadTexts(void)
{
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/texts/black-to-play.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _texts.blackToPlay = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_texts.blackToPlay == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/texts/white-to-play.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _texts.whiteToPlay = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_texts.whiteToPlay == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/texts/white-won.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _texts.whiteWon = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_texts.whiteWon == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/texts/black-won.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _texts.blackWon = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_texts.blackWon == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/texts/draw.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _texts.draw = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_texts.draw == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;
}

void    visualGame::loadLetters(void)
{
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/letters/a.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _letters.a = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_letters.a == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/letters/b.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _letters.b = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_letters.b == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/letters/c.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _letters.c = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_letters.c == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/letters/d.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _letters.d = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_letters.d == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/letters/e.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _letters.e = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_letters.e == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/letters/f.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _letters.f = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_letters.f == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/letters/g.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _letters.g = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_letters.g == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/letters/h.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _letters.h = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_letters.h == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;
}

void    visualGame::loadNumbers(void)
{
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/numbers/1.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _numbers.one = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_numbers.one == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/numbers/2.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _numbers.two = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_numbers.two == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/numbers/3.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _numbers.three = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_numbers.three == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/numbers/4.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _numbers.four = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_numbers.four == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/numbers/5.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _numbers.five = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_numbers.five == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/numbers/6.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _numbers.six = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_numbers.six == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/numbers/7.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _numbers.seven = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_numbers.seven == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/numbers/8.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _numbers.eight = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_numbers.eight == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;
}

void    visualGame::loadSymbols(void)
{
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/symbols/plus.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _symbols.plus = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_symbols.plus == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/symbols/moins.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;
    _symbols.moins = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_symbols.moins == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;
}

void    visualGame::loadTexture(const char type, const char color, const char *path)
{
    _baseCheck = 0;
    _baseSurface = SDL_LoadBMP(path);
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;

    if (type == 'K' && color == 'w')
        _whiteTextures.king = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (type == 'Q' && color == 'w')
        _whiteTextures.queen = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (type == 'N' && color == 'w')
        _whiteTextures.knight = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (type == 'B' && color == 'w')
        _whiteTextures.bishop = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (type == 'R' && color == 'w')
        _whiteTextures.rook = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (type == 'P' && color == 'w')
        _whiteTextures.pawn = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);

    if (type == 'K' && color == 'b')
        _blackTextures.king = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (type == 'Q' && color == 'b')
        _blackTextures.queen = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (type == 'N' && color == 'b')
        _blackTextures.knight = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (type == 'B' && color == 'b')
        _blackTextures.bishop = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (type == 'R' && color == 'b')
        _blackTextures.rook = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (type == 'P' && color == 'b')
        _blackTextures.pawn = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);

    SDL_FreeSurface(_baseSurface);
    _baseCheck = 0;
}

void    visualGame::loadWhiteTextures(void)
{
    loadTexture('K', 'w', "./materials/images/white/king.bmp");
    loadTexture('Q', 'w', "./materials/images/white/queen.bmp");

    loadTexture('N', 'w', "./materials/images/white/knight.bmp");
    loadTexture('B', 'w', "./materials/images/white/bishop.bmp");
    loadTexture('R', 'w', "./materials/images/white/rook.bmp");

    loadTexture('P', 'w', "./materials/images/white/pawn.bmp");
}

void    visualGame::loadBlackTextures(void)
{
    loadTexture('K', 'b', "./materials/images/black/king.bmp");
    loadTexture('Q', 'b', "./materials/images/black/queen.bmp");

    loadTexture('N', 'b', "./materials/images/black/knight.bmp");
    loadTexture('B', 'b', "./materials/images/black/bishop.bmp");
    loadTexture('R', 'b', "./materials/images/black/rook.bmp");

    loadTexture('P', 'b', "./materials/images/black/pawn.bmp");
}

void    visualGame::loadBoardTextures(void)
{
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/images/board.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;

    _boardTexture = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_boardTexture == NULL)
        { _error = true; return ; }

    SDL_FreeSurface(_baseSurface);

    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/images/checkmate-white.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;

    _checkMateWhiteTexture = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_checkMateWhiteTexture == NULL)
        { _error = true; return ; }

    SDL_FreeSurface(_baseSurface);

    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/images/checkmate-black.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;

    _checkMateBlackTexture = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_checkMateBlackTexture == NULL)
        { _error = true; return ; }

    SDL_FreeSurface(_baseSurface);

    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/images/promotion.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;

    _promotionTexture = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_promotionTexture == NULL)
        { _error = true; return ; }

    SDL_FreeSurface(_baseSurface);

    _baseCheck = 0;
}

void    visualGame::loadArrowTexture(void)
{
    _baseCheck = 0;

    _baseSurface = SDL_LoadBMP("./materials/images/arrow.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _baseCheck = 1;

    _arrowTexture = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_arrowTexture == NULL)
        { _error = true; return ; }

    SDL_FreeSurface(_baseSurface);
}

void    visualGame::loadTextures(void)
{
    loadTexts();

    if (_error == false)
        loadLetters();
    if (_error == false)
        loadNumbers();
    if (_error == false)
        loadSymbols();

    if (_error == false)
        loadBoardTextures();

    if (_error == false)
        loadArrowTexture();

    if (_error == false)
        loadWhiteTextures();
    
    if (_whiteTextures.bishop == NULL || _whiteTextures.king == NULL
        || _whiteTextures.knight == NULL || _whiteTextures.pawn == NULL
        || _whiteTextures.queen == NULL || _whiteTextures.rook == NULL)
        { _error = true; return ; }
    
    if (_error == false)
        loadBlackTextures();

    if (_blackTextures.bishop == NULL || _blackTextures.king == NULL
        || _blackTextures.knight == NULL || _blackTextures.pawn == NULL
        || _blackTextures.queen == NULL || _blackTextures.rook == NULL)
        { _error = true; return ; }

    if (_error == false)
        loadTexts();
}
