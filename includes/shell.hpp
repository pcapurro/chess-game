#ifndef SHELL_HPP
# define SHELL_HPP

# include "game.hpp"

void	printTitle(void);
void	initWelcome(void);

void	printGradually(const string str, const int value);
void	printLoading(void);

int		initializeShellGame(const bool sandBoxMode, const bool blindMode);

void	printInvalidArguments(void);
int		main(const int argc, const char **argv);

#endif