#include "Game.hpp"
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

void	printGradually(const std::string str, const int value)
{
	std::string	points;

	for (int i = 0; i != 4; i++)
	{
		cout << "\033[1A" << str << points << std::flush << endl;
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
	std::string	input;

	printTitle();
	std::getline(std::cin, input);
	if (std::cin.fail() == true)
		throw std::runtime_error("getline() failed");
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
