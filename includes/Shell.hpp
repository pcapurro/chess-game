#ifndef SHELL_HPP
# define SHELL_HPP

# include "Game.hpp"

void	printTitle(void);
void	initWelcome(void);

void	printGradually(const std::string str, const int value);
void	printLoading(void);

int		initializeShellGame(const bool sandBoxMode, const bool blindMode);

void	printInvalidArguments(void);
int		registerArguments(const char** argv, bool& sandBoxMode, bool& blindMode);

int		main(const int argc, const char** argv);

#endif