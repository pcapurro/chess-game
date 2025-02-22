#include "Game.hpp"
#include "ShellGame/ShellGame.hpp"

void	printInvalidArguments(void)
{
	cerr << "Error! Invalid arguments." << endl;
	cerr << "Usage: ./shell-chess [--sandbox/-s] or/and [--blind-mode/-b]" << endl;
}

void	printHelp(void)
{
	cout << "Play a chess game against Stockfish from the terminal." << endl;
	cout << "Usage: ./shell-chess [--sandbox/-s] or/and [--blind-mode/-b]" << endl;
	cout << endl;

	cout << "Options:" << endl;
	cout << "--sandbox (or -s)		: play against yourself" << endl;
	cout << "--blind-mode (or -b)		: play without the board" << endl;
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
		if (isHelp(argv) == true)
			{ printHelp(); return (0); }

		bool	sandBoxMode = false;
		bool	blindMode = false;

		if (argc != 1 && registerArguments(argv, sandBoxMode, blindMode) != 0)
			{ printInvalidArguments(); return (1); }

		ShellGame	gameShell(blindMode, sandBoxMode);

		gameShell.shellRoutine();
	}
	catch (const std::exception& except)
	{
		cerr << except.what() << endl;
		return (1);
	}

	return (0);
}
