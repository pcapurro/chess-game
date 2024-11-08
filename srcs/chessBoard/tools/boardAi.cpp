#include "../chessBoard.hpp"

string  chessBoard::getAiNextMove(const int aiSide)
{
	if (isCheckMateNextMove(true) == true) // defeat in 1 move
		cout << "player can checkmate next move" << endl;
	else
		cout << "player can't checkmate next move" << endl;

	++_turn % 2 == 0 ? _color = "white" : _color = "black";

	if (isCheckMateNextMove(true) == true) // victory in 1 move
		cout << "ai can win next move" << endl;
	else
		cout << "ai can't win next move" << endl;

	--_turn % 2 == 0 ? _color = "white" : _color = "black";

	static int i = 0;

	i++;

	if (i == 1)
		return ("Pe7e5");
	if (i == 2)
		return ("Qd8f6");
	if (i == 3)
		return ("Bf8c5");
	if (i == 4)
		return ("Qf6f2");

	return ("Qf6f2");
}
