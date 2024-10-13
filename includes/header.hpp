#ifndef HEADER_HPP
# define HEADER_HPP

# include <iostream>
# include <string>

# include "game/chessBoard.hpp"
# include "game/algebraicChecker.hpp"

using namespace std;

void    printWelcome(void);
void    initWelcome(void);

void    printLoading(void);

int     main(int argc, char **argv);

#endif