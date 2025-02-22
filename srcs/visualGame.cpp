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

void	printHelp(void)
{
	cout << "Play a chess game against Stockfish." << endl;
	cout << "Usage: ./chess-game [--sandbox/-s]" << endl;
	cout << endl;

	cout << "Options:" << endl;
	cout << "--sandbox (or -s)			: play against yourself" << endl;
	cout << endl;

	cout << "For more information, please read README.md." << endl;
}

bool	isHelp(const char** argv)
{
	for (int i = 1; argv[i] != NULL; i++)
	{
		if (std::string(argv[i]) == "--help")
			return (true);

		if (std::string(argv[i]) == "-h")
			return (true);
	}

	return (false);
}

int	registerArguments(const char** argv, bool& sandBoxMode)
{
	for (int i = 1; argv[i] != NULL; i++)
	{
		if (sandBoxMode == false \
			&& (std::string(argv[i]) == "--sandbox" || std::string(argv[i]) == "-s"))
			sandBoxMode = true;
		else
			return (1);
	}

	return (0);
}

int	main(const int argc, const char** argv)
{
	try
	{
		if (isHelp(argv) == true)
			{ printHelp(); return (0); }

		bool	sandBoxMode = false;

		if (argc != 1 && registerArguments(argv, sandBoxMode) != 0)
			{ printInvalidArguments(); return (1); }

		initializeVisualGame(sandBoxMode);
	}
	catch (const std::exception& except)
	{
		cerr << except.what() << endl;
		return (1);
	}

	return (0);
}
