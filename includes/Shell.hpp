#ifndef SHELL_HPP
# define SHELL_HPP

# include "Game.hpp"

int		initializeShellGame(const bool sandBoxMode, const bool blindMode);

void	printInvalidArguments(void);
int		registerArguments(const char** argv, bool& sandBoxMode, bool& blindMode);

int		main(const int argc, const char** argv);

#endif