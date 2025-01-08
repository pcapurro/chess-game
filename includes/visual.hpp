#ifndef VISUAL_HPP
# define VISUAL_HPP

# include "game.hpp"

# include <SDL2/SDL.h>

int		initializeVisualGame(const bool sandBoxMode);

void	printInvalidArguments(void);
int		main(const int argc, const char** argv);

#endif