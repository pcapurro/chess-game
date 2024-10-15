#ifndef HEADER_HPP
# define HEADER_HPP

# include <iostream>
# include <string>
# include <algorithm>

# include <vector>
# include <map>

# include <unistd.h>

# include "../srcs/objects/chessBoard.hpp"
# include "../srcs/objects/algebraicParser.hpp"

# define ERASE_LINE "\033[2K"

# define RED "\033[31m"
# define YELLOW "\033[33m"
# define GREEN "\033[3m"

# define COLOR_E "\033[0m"

using namespace std;

void    printTitle(void);
void    initWelcome(void);

void    printGradually(const string str, const int value);
void    printLoading(void);

void    systemError(void);
int     main(int argc, char **argv);

#endif