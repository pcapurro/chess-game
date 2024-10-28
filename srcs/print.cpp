#include "../include/shellChess.hpp"

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
        if (value == 1)
            sleep(1);
        else
            usleep(500);
    }
}

void    printLoading(void)
{
    printGradually("Loading", 1);
    cout << GREEN << "Game is ready." << COLOR_E << endl;
    sleep(1);
    cout << endl;
}

void    initWelcome(void)
{
    string  input;
    printTitle();
    getline(cin, input);
    if (cin.fail() == true)
        systemFailed();
    cout << "\033[2A" << ERASE_LINE << endl;
}

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
