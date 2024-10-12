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

int main(int argc, char **argv)
{
    printWelcome();
    (void) argc;
    (void) argv;
    return (0);
}