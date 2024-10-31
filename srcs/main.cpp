#include "../include/shellChess.hpp"

#include "shellGame/shellGame.hpp"
#include "visualGame/visualGame.hpp"

int validateArguments(const int argc, const char **argv)
{
    if (argc == 1)
        return (SUCCESS);
    if (argc == 2)
    {
        if (string(argv[1]) == "--no-visual")
            return (SUCCESS);
        if (string(argv[1]) == "--sandbox")
            return (SUCCESS);
    }
    if (argc == 3)
    {
        if (string(argv[1]) == "--no-visual"
            && string(argv[2]) == "--blind-mode")
            return (SUCCESS);

        if (string(argv[1]) == "--no-visual"
            && string(argv[2]) == "--sandbox")
            return (SUCCESS);

    }
    if (argc == 4)
    {
        if (string(argv[1]) == "--no-visual"
            && string(argv[2]) == "--blind-mode"
            && string(argv[3]) == "--sandbox")
            return (SUCCESS);

        if (string(argv[1]) == "--no-visual"
            && string(argv[2]) == "--sandbox"
            && string(argv[3]) == "--blind-mode")
            return (SUCCESS);
    }
    return (FAIL);
}

void    printInvalidArguments(void)
{
    cerr << "Error! Invalid arguments." << endl;
    cerr << "Usage: ./shell-chess [--no-visual] [--blind-mode] or/and [--sandbox]" << endl;
}

int initializeVisualGame(const bool sandBoxMode)
{
    visualGame  *gameVisual;

    gameVisual = new (nothrow) visualGame (sandBoxMode);
    if (gameVisual == nullptr)
        return (1);

    gameVisual->visualRoutine();

    delete gameVisual;
    if (gameVisual->fail() == true)
        return (1);

    return (0);
}

int initializeShellGame(const bool sandBoxMode, const bool blindMode)
{
    initWelcome();
    printLoading();

    shellGame   *gameShell;
            
    gameShell = new (nothrow) shellGame(blindMode, sandBoxMode);
    if (gameShell == nullptr)
        return (1);

    gameShell->shellRoutine();

    delete gameShell;
    if (gameShell->fail() == true)
        return (1);
    
    return (0);
}

int main(const int argc, const char **argv)
{
    if (validateArguments(argc, argv) != SUCCESS)
        return (printInvalidArguments(), 1);
    else
    {
        bool    sandBoxMode = false;
        bool    blindMode = false;

        if (argc == 2 && string(argv[1]) == "--sandbox" || argc == 3 && string(argv[2]) == "--sandbox"
            || argc == 4 && string(argv[2]) == "--sandbox" || argc == 4 && string(argv[3]) == "--sandbox")
            sandBoxMode = true;

        if (argc == 3 && string(argv[2]) == "--blind-mode" || argc == 4 && string(argv[2]) == "--blind-mode"
            || argc == 4 && string(argv[3]) == "--blind-mode")
            blindMode = true;

        if (argc == 1 || argc == 2 && string(argv[1]) == "--sandbox")
        {
            if (initializeVisualGame(sandBoxMode) != 0)
                return (1);
        }
        else
        {
            if (initializeShellGame(sandBoxMode, blindMode) != 0)
                return (1);
        }
    }
    return (0);
}
