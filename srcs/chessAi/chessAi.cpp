#include "chessAi.hpp"

chessAi::chessAi(void) {;}

chessAi::~chessAi(void) {;}

string	chessAi::getNextMove(const chessBoard *board, const int aiSide)
{
	chessBoard	newBoard(board);
	string			nextMove;
	vector<string>	legalMoves;
	
	legalMoves = newBoard.getAvailaibleMoves();

	cout << "possibles moves for ai >" << endl;
	for (int i = 0; i != legalMoves.size(); i++)
		cout << legalMoves.at(i) << " ; ";
	cout << endl;

	// if (newBoard.isCheckMateNextMove(true) == true) // defeat in 1 move
	// 	cout << "player can checkmate next move" << endl;
	// else
	// 	cout << "player can't checkmate next move" << endl;

	// ++newBoard._turn % 2 == 0 ? newBoard._color = "white" : newBoard._color = "black";

	// if (newBoard.isCheckMateNextMove(true) == true) // victory in 1 move
	// 	cout << "ai can win next move" << endl;
	// else
	// 	cout << "ai can't win next move" << endl;

	// newBoard.printBoard(1);

	// --newBoard._turn % 2 == 0 ? newBoard._color = "white" : newBoard._color = "black";

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
