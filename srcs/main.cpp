#include "../include/shellChess.hpp"

int main(const int argc, const char **argv)
{
    if (argc > 3
        || (argc == 2 && string(argv[1]) != "--no-visual")
        || (argc == 3 && string(argv[1]) != "--no-visual" && string(argv[2]) != "--blind-mode"))
    {
        cerr << "Error! Invalid arguments." << endl;
        cerr << "Usage: ./shell-chess [--no-visual] [--blind-mode]" << endl;
        return (1);
    }
    else
    {
        if (argc == 1)
        {
            if (initializeVisualGame() != 0)
                return (1);
        }
        else
        {
            initWelcome();
            printLoading();

            if (initializeShellGame(argc) != 0)
                return (1);
        }
    }
    return (0);
}
