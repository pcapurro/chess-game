#include "Game.hpp"
#include "ShellGame/ShellGame.hpp"

void	printInvalidArguments(void)
{
	cerr << "Error! Invalid arguments." << endl;
	cerr << "Usage: ./shell-chess [--sandbox] or/and [--blind-mode]" << endl;
}

int	initializeShellGame(const bool sandBoxMode, const bool blindMode)
{
	ShellGame*	gameShell;
			
	gameShell = new (std::nothrow) ShellGame(blindMode, sandBoxMode);

	gameShell->shellRoutine();

	delete gameShell;
	
	return (0);
}

int	registerArguments(const char** argv, bool& sandBoxMode, bool& blindMode)
{
	for (int i = 1; argv[i] != NULL; i++)
	{
		if (sandBoxMode == false \
			&& (std::string(argv[i]) == "--sandbox" || std::string(argv[i]) == "-s"))
			sandBoxMode = true;
		else if (blindMode == false \
			&& (std::string(argv[i]) == "--blind-mode" || std::string(argv[i]) == "-b"))
			blindMode = true;
		else
			return (1);
	}

	return (0);
}

int	main(const int argc, const char** argv)
{
	try
	{
		bool	sandBoxMode = false;
		bool	blindMode = false;

		if (argc != 1 && registerArguments(argv, sandBoxMode, blindMode) != 0)
			{ printInvalidArguments(); return (1); }

		initializeShellGame(sandBoxMode, blindMode);
	}
	catch (const std::exception& except)
	{
		cerr << except.what() << endl;
		return (1);
	}

	return (0);
}
