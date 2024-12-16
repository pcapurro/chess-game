#ifndef CHESSGAME_HPP
# define CHESSGAME_HPP

# include <iostream>
# include <string>

# include <algorithm>
# include <vector>
# include <stack>
# include <map>

# include <cstdlib>
# include <cstdio>
# include <fstream>

# include <unistd.h>

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

using namespace std;

int     memoryFailed(void);
int     systemFailed(void);

#endif