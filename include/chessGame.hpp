#ifndef CHESSGAME_HPP
# define CHESSGAME_HPP

# include <iostream>
# include <string>
# include <algorithm>
# include <vector>
# include <map>
# include <cstdlib>
# include <unistd.h>

# include <SDL2/SDL.h>

using namespace std;

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

void    printTitle(void);
void    initWelcome(void);

void    printGradually(const string str, const int value);
void    printLoading(void);

int     memoryFailed(void);
int     systemFailed(void);

int 	initializeShellGame(const bool sandBoxMode, const bool blindMode);
int 	initializeVisualGame(const bool sandBoxMode);

void    printInvalidArguments(void);
int 	validateArguments(const int argc, const char **argv);

int     main(const int argc, const char **argv);

#endif