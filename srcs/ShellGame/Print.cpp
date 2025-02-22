#include "ShellGame/ShellGame.hpp"

void	ShellGame::printTitle(void)
{
	cout << "                         #-# ############ #-#                            " << endl;
	cout << "##           #-######-#                         #-######-#           ##  " << endl;
	cout << "#                 #/-/# ♛ ♞ ♝ shell-chess ♛ ♞ ♝ #\\-\\#                 #" << endl;
	cout << "#        #-######-#       #-# by pcapurro #-#       #-######-#        #  " << endl;
	cout << "##                #-######-#               #-######-#                ##  " << endl;
	cout << endl;
	cout << "                    ♖ ## Press ENTER to start! ## ♖                      " << endl;
}

void	ShellGame::printGradually(const std::string str, const int value)
{
	std::string	points;

	for (int i = 0; i != 4; i++)
	{
		cout << "\033[1A" << str << points << std::flush << endl;
		points = points + ".";
		if (value == 1)
			std::this_thread::sleep_for(std::chrono::seconds(1));
		else
			std::this_thread::sleep_for(std::chrono::microseconds(5000));
	}
}

void	ShellGame::printGame(void)
{
	std::cout << "\033[2J\033[H" << std::endl;

	_board->printBoard(_aiSide);
}
