#ifndef SHELLCHESSVISUAL_HPP
# define SHELLCHESSVISUAL_HPP

# include <SDL2/SDL.h>

# include "shellChess.hpp"
# include "shellChessClassic.hpp"

int     validateArguments(const char *arg1, const char *arg2);
int     visualGame(void *gameObject);

#endif