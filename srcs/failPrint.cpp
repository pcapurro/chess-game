#include "../includes/game.hpp"

int systemFailed(void)
{
    cout << "\033[1A" << ERASE_LINE << endl << ERASE_LINE;
    cerr << "System failed. Closing the game..." << endl;
    return (1);
}

int memoryFailed(void)
{
    cout << "\033[1A" << ERASE_LINE << endl << ERASE_LINE;
    cerr << "Memory allocation failed. Closing the game..." << endl;
    return (1);
}
