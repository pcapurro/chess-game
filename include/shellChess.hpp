#ifndef SHELLCHESS_HPP
# define SHELLCHESS_HPP

# include <iostream>
# include <string>
# include <algorithm>
# include <vector>
# include <map>
# include <unistd.h>

# include <SDL2/SDL.h>

# define ERR -1
# define SUCCESS 0
# define FAIL 1

# define ERASE_LINE "\033[2K"

# define RED "\033[31m"
# define YELLOW "\033[33m"
# define GREY "\033[90m"
# define ORANGE "\033[38;5;208m"
# define GREEN "\033[32m"

# define COLOR_E "\033[0m"

# include "../srcs/algebraicParser/algebraicParser.hpp"
# include "../srcs/chessBoard/chessBoard.hpp"

using namespace std;

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

void    printTitle(void);
void    initWelcome(void);

void    printGradually(const string str, const int value);
void    printLoading(void);

int     memoryFailed(void);
int     systemFailed(void);

int     shellGame(const int argc);
int     visualGame(void);

int     main(const int argc, const char **argv);

#endif