#include "../includes/Shell.hpp"
#include "ShellGame/ShellGame.hpp"

void	printTitle(void)
{
	cout << "                         #-# ############ #-#                            " << endl;
	cout << "##           #-######-#                         #-######-#           ##  " << endl;
	cout << "#                 #/-/# ♛ ♞ ♝ shell-chess ♛ ♞ ♝ #\\-\\#                 #" << endl;
	cout << "#        #-######-#       #-# by pcapurro #-#       #-######-#        #  " << endl;
	cout << "##                #-######-#               #-######-#                ##  " << endl;
	cout << "                                                                         " << endl;
	cout << "                    ♖ ## Press ENTER to start! ## ♖                      " << endl;
}

void	printGradually(const string str, const int value)
{
	string	points;

	for (int i = 0; i != 4; i++)
	{
		cout << "\033[1A" << str << points << flush << endl;
		points = points + ".";
		if (value == 1)
			sleep(1);
		else
			usleep(5000);
	}
}

void	printLoading(void)
{
	printGradually("Loading", 1);
	cout << GREEN << "Game is ready." << COLOR_E << endl;
	sleep(1);
	cout << endl;
}

void	initWelcome(void)
{
	string	input;

	printTitle();
	getline(cin, input);
	if (cin.fail() == true)
		systemFailed(true, "getline() failed.");
	else
		cout << "\033[2A" << ERASE_LINE << endl;
}

void	printInvalidArguments(void)
{
	cerr << "Error! Invalid arguments." << endl;
	cerr << "Usage: ./shell-chess [--sandbox] or/and [--blind-mode]" << endl;
}

int	initializeShellGame(const bool sandBoxMode, const bool blindMode)
{
	initWelcome();
	printLoading();

	ShellGame*	gameShell;
			
	gameShell = new (nothrow) ShellGame(blindMode, sandBoxMode);
	if (gameShell == nullptr)
		return (1);

	if (gameShell->fail() == true)
		{ delete gameShell; return (1); }

	gameShell->shellRoutine();

	if (gameShell->fail() == true)
		{ delete gameShell; return (1); }

	delete gameShell;
	
	return (0);
}

int	validateArguments(const int argc, const char** argv)
{
	if (argc == 1)
		return (0);
	if (argc == 2)
	{
		if (string(argv[1]) != "--sandbox" && string(argv[1]) != "--blind-mode")
			return (1);
		return (0);
	}
	if (argc == 3)
	{
		if (string(argv[1]) != "--sandbox" && string(argv[1]) != "--blind-mode")
			return (1);
		if (string(argv[2]) != "--sandbox" && string(argv[2]) != "--blind-mode")
			return (1);

		if (string(argv[1]) == string(argv[2]))
			return (1);

		return (0);
	}

	return (1);
}

int	main(const int argc, const char** argv)
{
	if (validateArguments(argc, argv) == 1)
		printInvalidArguments();
	else
	{
		bool	sandBoxMode = false;
		bool	blindMode = false;

		if (argc > 1)
		{
			if (string(argv[1]) == "--blind-mode" \
				|| (argc == 3 && string(argv[2]) == "--blind-mode"))
				blindMode = true;
			if (string(argv[1]) == "--sandbox" \
				|| (argc == 3 && string(argv[2]) == "--sandbox"))
				sandBoxMode = true;
		}

		if (initializeShellGame(sandBoxMode, blindMode) != 0)
			return (1);
	}

	return (0);
}
