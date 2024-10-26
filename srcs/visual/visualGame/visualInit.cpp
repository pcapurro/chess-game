#include "visualGame.hpp"

visualGame::visualGame(const int width, const int heigth) : _width(width), _height(heigth)
{
    _turn = 1;
    _dropped = true;

    initializeGame();
    loadTextures();
}

void    visualGame::initializeGame(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    
    _mainWindow = SDL_CreateWindow("shell-chess", 100, 100, \
        _width, _height, SDL_WINDOW_SHOWN);

    _mainRenderer = SDL_CreateRenderer(_mainWindow, -1, \
        SDL_RENDERER_ACCELERATED);

    _normalCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    _playCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
}
