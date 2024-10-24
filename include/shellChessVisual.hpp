#ifndef SHELLCHESSVISUAL_HPP
# define SHELLCHESSVISUAL_HPP

# include "shellChess.hpp"
# include "shellChessClassic.hpp"

# include <SDL2/SDL.h>

typedef struct s_textures
{
    SDL_Texture     *king;
    SDL_Texture     *queen;

    SDL_Texture     *bishop;
    SDL_Texture     *knight;
    SDL_Texture     *rook;

    SDL_Texture     *pawn;

}   t_textures;

typedef struct s_game
{
    SDL_Window      *mainWindow;
    SDL_Renderer    *mainRenderer;

    SDL_Texture     *boardTexture;
    SDL_Surface     *baseSurface;
    t_textures      whiteTextures;
    t_textures      blackTextures;

    bool            error;
    bool            state;

}   t_game;


int     visualGame(void);

#endif