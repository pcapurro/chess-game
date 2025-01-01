#ifndef VISUAL_HPP
# define VISUAL_HPP

# include "game.hpp"

# include <SDL2/SDL.h>

# define WIDTH 850
# define HEIGHT 800

int		initializeVisualGame(const bool sandBoxMode);

void	printInvalidArguments(void);
int		main(const int argc, const char **argv);

#endif