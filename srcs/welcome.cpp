#include "../includes/header.hpp"

void    printWelcome(void)
{
    cout << "                         #-# ############ #-#                            " << endl;
    cout << "##           #-######-#                         #-######-#           ##  " << endl;
    cout << "#                 #/-/# ♛ ♞ ♝ shell-chess ♛ ♞ ♝ #\\-\\#                 #" << endl;
    cout << "#        #-######-#       #-# by pcapurro #-#       #-######-#        #  " << endl;
    cout << "##              #-######-#               #-######-#                  ##  " << endl;
    cout << "                                                                         " << endl;
    cout << "                    ♖ ## Press ENTER to start! ## ♖                      " << endl;
}

void    initWelcome(void)
{
    printWelcome();
    
    string  input;
    input = "42";
    while (input.length() != 0)
    {
        getline(cin, input);
        if (cin.fail() == true)
            exit(1);
    }
}
