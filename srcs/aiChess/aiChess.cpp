#include "aiChess.hpp"
#include "../chessBoard/chessBoard.hpp"

aiChess::aiChess(void) {;}

aiChess::~aiChess(void) {;}

string	aiChess::getNextMove(chessBoard *board, const int aiSide)
{
	string		aiColor;
	string		playerColor;

	chessBoard	newBoard;

	if (aiSide % 2 == 0)
		aiColor = "white", playerColor = "black";
	else
		aiColor = "black", playerColor = "white";

	newBoard = board;

	vector<string>	moves;
	for (int i = 0; i != 64; i++)
	{
		if (newBoard._board.at(i).piece != NULL)
		{
			moves = newBoard.getPossibleMoves(newBoard._board.at(i).coord);

			for (int k = 0; k != moves.size(); k++)
			{
				cout << "testing " << moves.at(k) << endl;
				newBoard.playMove({moves.at(k), '-', moves.at(k)[0], \
					(string(1, moves.at(k)[1]) + moves.at(k)[2]), moves.at(k).c_str() + 3, false}, false);
				if (newBoard.isCheckMate() == true)
					{ cout << "checkmate possible " << endl;}
				newBoard = board;
			}
		}
	}

	static int i = 0;
	vector<string> moves2;
	
	moves2.push_back(" ");
	moves2.push_back("Pe7e5");
	moves2.push_back("Pa7a5");
	moves2.push_back("Pa5a4");

	i++;

	return (moves2.at(i));
}

// 0. endgame ou start/middle game ?
// 2. échec et mat dans 1 move ?
// 3. échec et mat dans 2 moves ?

// 1. = move sans perte ?
// 4. = move empêche le roque (= menace case roque + pas de perte) ?
// 5. = move protégé ?