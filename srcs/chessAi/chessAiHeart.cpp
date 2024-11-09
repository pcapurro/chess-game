#include "chessAi.hpp"

void	chessAi::checkMateMove(string *nextMove)
{
	if (*nextMove != "")
		return ;
}

void	chessAi::attackMove(string *nextMove)
{
	if (*nextMove != "")
		return ;
}

void	chessAi::passiveMove(string *nextMove)
{
	if (*nextMove != "")
		return ;
}

void	chessAi::defendMove(string *nextMove)
{
	if (*nextMove != "")
		return ;
}

void	chessAi::endGameMove(string *nextMove)
{
	if (*nextMove != "")
		return ;
}

void	chessAi::randomMove(string *nextMove)
{
	if (*nextMove != "")
		return ;
}

string	chessAi::getNextMove(const chessBoard *board, const int aiSide)
{
	string			nextMove;

	chessBoard		newBoard(board);
	vector<string>	legalMoves = getLegalMoves(&newBoard);

	if (newBoard.isCheckMateNextMove(true) == true)
		checkMateMove(&nextMove);
	else
	{
		if (newBoard.isCheckMateNextMove(true, true) == true)
			defendMove(&nextMove);
		else
		{
			if (newBoard.isEndGame() == false)
				attackMove(&nextMove), passiveMove(&nextMove);
			else
				endGameMove(&nextMove);
		}
	}
	randomMove(&nextMove);

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
