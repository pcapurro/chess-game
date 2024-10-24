#ifndef SHELLCHESSVISUAL_HPP
# define SHELLCHESSVISUAL_HPP

# include <SDL2/SDL.h>

# include "shellChess.hpp"
# include "shellChessClassic.hpp"

int     validateArguments(const char *argOne, const char *argTwo);
int     visualGame(void *gameObjectPtr, void *chessBoardPtr);

#endif