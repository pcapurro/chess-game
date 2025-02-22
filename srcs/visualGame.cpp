#include "Game.hpp"
#include "VisualGame/VisualGame.hpp"

int	initializeVisualGame(const bool sandBoxMode)
{
	VisualGame*	gameVisual;

	gameVisual = new (std::nothrow) VisualGame (sandBoxMode);

	gameVisual->visualRoutine();

	delete gameVisual;

	return (0);
}

void	printInvalidArguments(void)
{
	cerr << "Error! Invalid arguments." << endl;
	cerr << "Usage: ./chess-game [--sandbox]" << endl;
}

int	main(const int argc, const char** argv)
{
	try
	{
		if (argc > 2 || (argc == 2 && std::string(argv[1]) != "--sandbox"))
			printInvalidArguments();
		else
		{
			bool	sandBoxMode = false;

			if (argc == 2)
				sandBoxMode = true;

			if (initializeVisualGame(sandBoxMode) != 0)
				return (1);
		}
	}
	catch (const std::exception& except)
	{
		cerr << except.what() << endl;
		return (1);
	}

	return (0);
}
