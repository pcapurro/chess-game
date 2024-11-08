#include "../chessBoard.hpp"

string  chessBoard::getAiNextMove(const int aiSide)
{
	if (isCheckMateNextMove(true) == true)
		cout << "player can checkmate next move" << endl;
	else
		cout << "player can't checkmate next move" << endl;

	static int i = 0;

	i++;

	if (i == 1)
		return ("Pa7a5");
	if (i == 2)
		return ("Pa5a4");
	if (i == 3)
		return ("Pa4a3");

	return ("Pe7e5");
}
