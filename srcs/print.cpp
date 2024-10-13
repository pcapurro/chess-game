#include "../includes/header.hpp"

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
    cout << "Game is ready." << endl;
    sleep(1);
    cout << endl;
}
