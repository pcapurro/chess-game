#include "visualGame.hpp"

void    visualGame::loadTexts(void)
{
    _baseSurface = SDL_LoadBMP("./materials/texts/black-to-play.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _texts.blackToPlay = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_texts.blackToPlay == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);

    _baseSurface = SDL_LoadBMP("./materials/texts/white-to-play.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _texts.whiteToPlay = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_texts.whiteToPlay == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);

    _baseSurface = SDL_LoadBMP("./materials/texts/white-won.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _texts.whiteWon = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_texts.whiteWon == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);

    _baseSurface = SDL_LoadBMP("./materials/texts/black-won.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _texts.blackWon = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_texts.blackWon == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);

    _baseSurface = SDL_LoadBMP("./materials/texts/draw.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _texts.draw = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_texts.draw == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);
}

void    visualGame::loadTexture(const char type, const char color, const char *path)
{
    _baseSurface = SDL_LoadBMP(path);
    if (_baseSurface == NULL)
        { _error = true; return ; }

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

void    visualGame::loadTextures(void)
{
    _baseSurface = SDL_LoadBMP("./materials/images/board.bmp");
    if (_baseSurface == NULL)
        { _error = true; return ; }
    _boardTexture = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    if (_boardTexture == NULL)
        { _error = true; return ; }
    SDL_FreeSurface(_baseSurface);

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
