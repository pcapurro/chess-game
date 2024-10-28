#include "visualGame.hpp"

visualGame::visualGame(const int width, const int heigth) : _width(width), _height(heigth)
{
    _error = false;

    setToDefault();
    setToNullPtr();

    initializeGame();
    if (_error == false)
        loadTextures();
    if (_error == false)
        loadTexts();
}

void    visualGame::setToDefault(void)
{
    _turn = 1;

    _input.action = '-';
    _input.obj = ' ';

    _input.dest.clear();
    _input.move.clear();
    _input.src.clear();

    _dropped = true;
    _sourceCoord.clear();
}

void    visualGame::setToNullPtr(void)
{
    _mainWindow = nullptr;
    _mainRenderer = nullptr;
    _normalCursor = nullptr;
    _playCursor = nullptr;

    _boardTexture = nullptr;
    _baseSurface = nullptr;
    _baseCheck = 0;

    _whiteTextures.bishop = nullptr;
    _whiteTextures.king = nullptr;
    _whiteTextures.knight = nullptr;
    _whiteTextures.pawn = nullptr;
    _whiteTextures.queen = nullptr;
    _whiteTextures.rook = nullptr;

    _blackTextures.bishop = nullptr;
    _blackTextures.king = nullptr;
    _blackTextures.knight = nullptr;
    _blackTextures.pawn = nullptr;
    _blackTextures.queen = nullptr;
    _blackTextures.rook = nullptr;

    _texts.blackToPlay = nullptr;
    _texts.blackWon = nullptr;
    _texts.draw = nullptr;
    _texts.whiteToPlay = nullptr;
    _texts.whiteWon = nullptr;
}

void    visualGame::initializeGame(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        { _error = true; return ; }
    
    _mainWindow = SDL_CreateWindow("shell-chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, \
        _width, _height, SDL_WINDOW_RESIZABLE);
    if (_mainWindow == NULL)
        { _error = true; return ; }

    _mainRenderer = SDL_CreateRenderer(_mainWindow, -1, \
        SDL_RENDERER_ACCELERATED);
    if (_mainRenderer == NULL)
        { _error = true; return ; }

    _normalCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    _playCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

    if (_normalCursor == NULL || _playCursor == NULL)
        { _error = true; return ; }
}
