#ifndef HEADER_HPP
# define HEADER_HPP

# include <iostream>
# include <string>
# include <algorithm>
# include <vector>
# include <map>
# include <unistd.h>

# define ERASE_LINE "\033[2K"

# define RED "\033[31m"
# define YELLOW "\033[33m"
# define GREEN "\033[32m"

# define COLOR_E "\033[0m"

# include "../srcs/algebraicParser/algebraicParser.hpp"
# include "../srcs/chessBoard/chessBoard.hpp"

using namespace std;

void    printTitle(void);
void    initWelcome(void);

void    printGradually(const string str, const int value);
void    printLoading(void);

void    systemError(void);
int     main(int argc, char **argv);

#endif