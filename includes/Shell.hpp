#ifndef SHELL_HPP
# define SHELL_HPP

# include "Game.hpp"

void	printHelp(void);
bool	isHelp(const char** argv);

void	printInvalidArguments(void);
int		registerArguments(const char** argv, bool& sandBoxMode, bool& blindMode);

int		main(const int argc, const char** argv);

#endif