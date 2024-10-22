#include "../include/header.hpp"

int main(const int argc, const char **argv)
{
    if (argc > 3 || (argc == 2 && string(argv[1]) != "--no-visual")
        || (argc == 3 && (string(argv[1]) != "--no-visual" || string(argv[2]) != "--blind")))
    {
        cerr << "Error! Invalid arguments." << endl;
        cerr << "Usage: ./shell-chess [--no-visual] [--blind]" << endl;
        return (1);
    }
    else
    {
        if (argc != 1)
        {
            initWelcome();
            printLoading();

            if (shellGame(argc) != 0)
                return (1);
        }
        else
            ;
    }
    return (0);
}
