#include "../include/header.hpp"

void    printTitle(void)
{
    cout << "                         #-# ############ #-#                            " << endl;
    cout << "##           #-######-#                         #-######-#           ##  " << endl;
    cout << "#                 #/-/# ♛ ♞ ♝ shell-chess ♛ ♞ ♝ #\\-\\#                 #" << endl;
    cout << "#        #-######-#       #-# by pcapurro #-#       #-######-#        #  " << endl;
    cout << "##                #-######-#               #-######-#                ##  " << endl;
    cout << "                                                                         " << endl;
    cout << "                    ♖ ## Press ENTER to start! ## ♖                      " << endl;
}

void    printGradually(const string str, const int value)
{
    string  points;

    for (int i = 0; i != 4; i++)
    {
        cout << "\033[1A" << str << points << flush << endl;
        points = points + ".";
        // if (value == 1)
        //     sleep(1);
        // else
        //     usleep(500);
    }
}

void    printLoading(void)
{
    printGradually("Loading", 1);
    cout << GREEN << "Game is ready." << COLOR_E << endl;
    // sleep(1);
    cout << endl;
}

void    systemFailed(void)
{
    cout << "\033[2A" << ERASE_LINE << endl << ERASE_LINE;
    cout << "System failed. Closing the game..." << endl;
}

void    memoryFailed(void)
{
    cout << "\033[2A" << ERASE_LINE << endl << ERASE_LINE;
    cout << "Memory allocation failed. Closing the game..." << endl;
}
