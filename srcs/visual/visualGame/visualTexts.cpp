#include "visualGame.hpp"

void    visualGame::loadTexts(void)
{
    _baseSurface = SDL_LoadBMP("./materials/black-to-play.bmp");
    _texts.blackToPlay = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    SDL_FreeSurface(_baseSurface);

    _baseSurface = SDL_LoadBMP("./materials/white-to-play.bmp");
    _texts.whiteToPlay = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    SDL_FreeSurface(_baseSurface);

    _baseSurface = SDL_LoadBMP("./materials/white-won.bmp");
    _texts.whiteWon = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    SDL_FreeSurface(_baseSurface);

    _baseSurface = SDL_LoadBMP("./materials/black-won.bmp");
    _texts.blackWon = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    SDL_FreeSurface(_baseSurface);

    _baseSurface = SDL_LoadBMP("./materials/draw.bmp");
    _texts.draw = SDL_CreateTextureFromSurface(_mainRenderer, _baseSurface);
    SDL_FreeSurface(_baseSurface);
}
