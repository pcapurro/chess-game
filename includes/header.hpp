#ifndef HEADER_HPP
# define HEADER_HPP

# include <iostream>
# include <string>
# include <algorithm>

# include <unistd.h>

# include "game/chessBoard.hpp"
# include "game/algebraicChecker.hpp"

using namespace std;

void    printTitle(void);
void    initWelcome(void);

void    printGradually(const string str, const int value);
void    printLoading(void);

void    systemError(void);
int     main(int argc, char **argv);

#endif