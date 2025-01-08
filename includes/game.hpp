#ifndef CHESSGAME_HPP
# define CHESSGAME_HPP

# include <iostream>
# include <string>

# include <algorithm>
# include <vector>
# include <stack>

# include <fstream>
# include <sstream>

# include <cstdlib>
# include <cstdio>

# include <unistd.h>

# define ERASE_LINE "\033[2K"

# define RED "\033[31m"
# define YELLOW "\033[33m"
# define GREY "\033[90m"
# define ORANGE "\033[38;5;208m"
# define GREEN "\033[32m"

# define COLOR_E "\033[0m"

using namespace std;

int		memoryFailed(const bool value);
int		systemFailed(const bool value, const string message);

#endif