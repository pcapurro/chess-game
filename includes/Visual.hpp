#ifndef VISUAL_HPP
# define VISUAL_HPP

# include "Game.hpp"

# include <SDL2/SDL.h>

int		initializeVisualGame(const bool sandBoxMode);

void	printInvalidArguments(void);
int		registerArguments(const char** argv, bool& sandBoxMode);

int		main(const int argc, const char** argv);

#endif