#include "visualGame.hpp"

visualGame::~visualGame()
{
    if (_board != nullptr)
        delete _board;

    if (_textures != nullptr)
        delete _textures;

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
