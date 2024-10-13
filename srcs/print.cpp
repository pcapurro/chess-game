#include "../includes/header.hpp"

void    printGradually(const string str, const int value)
{
    string  points;

    for (int i = 0; i != 4; i++)
    {
        cout << "\033[1A" << str << points << flush << endl;
        points = points + ".";
        if (value == 1)
            sleep(1);
        else
            usleep(500);
    }
}

void    printLoading(void)
{
    printGradually("Loading", 1);
    cout << "Game is ready." << endl;
    sleep(1);
    cout << endl;
}
