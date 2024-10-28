#include "visualGame.hpp"

visualGame::visualGame(const int width, const int heigth) : _width(width), _height(heigth)
{
    setToDefault();

    initializeGame();
    if (_error == false)
        loadTextures();
    if (_error == false)
        loadTexts();
}

void    visualGame::setToDefault(void)
{
    _error = false;
    _turn = 1;
    _dropped = true;
    _sourceCoord.clear();
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
