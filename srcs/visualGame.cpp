#include "../includes/game.hpp"
#include "visualGame/visualGame.hpp"

int initializeVisualGame(const bool sandBoxMode)
{
    visualGame  *gameVisual;

    gameVisual = new (nothrow) visualGame (sandBoxMode);
    if (gameVisual == nullptr)
        return (1);

    if (gameVisual->fail() == true)
        { delete gameVisual; return (1); }

    gameVisual->visualRoutine();

    if (gameVisual->fail() == true)
        { delete gameVisual; return (1); }

    delete gameVisual;

    return (0);
}

void	printInvalidArguments(void)
{
    cerr << "Error! Invalid arguments." << endl;
    cerr << "Usage: ./chess-game [--sandbox]" << endl;
}

int	main(const int argc, const char **argv)
{
    if (argc > 2 || (argc == 2 && string(argv[1]) != "--sandbox"))
        printInvalidArguments();
    else
    {
        bool    sandBoxMode = false;

        if (argc == 2)
            sandBoxMode = true;

        if (initializeVisualGame(sandBoxMode) != 0)
            return (1);
    }

	return (0);
}
