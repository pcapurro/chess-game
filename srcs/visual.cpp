#include "../include/shellChess.hpp"

void    endGame(t_game *mainStr)
{
    if (mainStr->whiteTextures.pawn != nullptr)
        SDL_DestroyTexture(mainStr->whiteTextures.pawn);
    if (mainStr->whiteTextures.king != nullptr)
        SDL_DestroyTexture(mainStr->whiteTextures.king);
    if (mainStr->whiteTextures.queen != nullptr)
        SDL_DestroyTexture(mainStr->whiteTextures.queen);
    if (mainStr->whiteTextures.bishop != nullptr)
        SDL_DestroyTexture(mainStr->whiteTextures.bishop);
    if (mainStr->whiteTextures.knight != nullptr)
        SDL_DestroyTexture(mainStr->whiteTextures.knight);
    if (mainStr->whiteTextures.rook != nullptr)
        SDL_DestroyTexture(mainStr->whiteTextures.rook);

    if (mainStr->blackTextures.pawn != nullptr)
        SDL_DestroyTexture(mainStr->blackTextures.pawn);
    if (mainStr->blackTextures.king != nullptr)
        SDL_DestroyTexture(mainStr->blackTextures.king);
    if (mainStr->blackTextures.queen != nullptr)
        SDL_DestroyTexture(mainStr->blackTextures.queen);
    if (mainStr->blackTextures.bishop != nullptr)
        SDL_DestroyTexture(mainStr->blackTextures.bishop);
    if (mainStr->blackTextures.knight != nullptr)
        SDL_DestroyTexture(mainStr->blackTextures.knight);
    if (mainStr->blackTextures.rook != nullptr)
        SDL_DestroyTexture(mainStr->blackTextures.rook);

    if (mainStr->mainWindow != nullptr)
        SDL_DestroyWindow(mainStr->mainWindow);
    if (mainStr->mainRenderer != nullptr)
        SDL_DestroyRenderer(mainStr->mainRenderer);

    SDL_Quit();

    delete mainStr;
}

void    *initializeGame(t_game *mainStr)
{
    mainStr->mainWindow = SDL_CreateWindow("shell-chess", 100, 100, \
        700, 700, SDL_WINDOW_SHOWN);
    if (!mainStr->mainWindow)
        return (nullptr);

    mainStr->mainRenderer = SDL_CreateRenderer(mainStr->mainWindow, -1, \
        SDL_RENDERER_ACCELERATED);
    if (!mainStr->mainRenderer)
        return (nullptr);
    
    return (mainStr);
}

void    *loadTextures(t_game *mainStr)
{
    // mainStr->baseSurface = IMG_Load("./materials/board.png");
    // if (!mainStr->baseSurface)
        // return (nullptr);
    mainStr->boardTexture = SDL_CreateTextureFromSurface(mainStr->mainRenderer, mainStr->baseSurface);
    if (!mainStr->boardTexture)
        return (nullptr);
    SDL_FreeSurface(mainStr->baseSurface);

    return (mainStr);
}

int visualGame(void)
{
    t_game  *mainStr;

    mainStr = new (std::nothrow) t_game;
    if (mainStr == nullptr)
        return (1);
    else
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
            return (1);

        if (initializeGame(mainStr) == nullptr
            || loadTextures(mainStr) == nullptr)
            return (1);

        SDL_RenderClear(mainStr->mainRenderer);
        SDL_RenderCopy(mainStr->mainRenderer, mainStr->boardTexture, NULL, NULL);
        SDL_RenderPresent(mainStr->mainRenderer);

        SDL_Delay(6000);

        endGame(mainStr);
    }

    return (0);
}

// https://alexandre-laurent.developpez.com/tutoriels/sdl-2/creer-premieres-fenetres/