#include "chessAi.hpp"

void	chessAi::checkMateMove(void)
{
	if (_nextMove != "")
		return ;
}

void	chessAi::attackMove(void)
{
	if (_nextMove != "")
		return ;
}

void	chessAi::passiveMove(void)
{
	if (_nextMove != "")
		return ;
}

void	chessAi::defendMove(void)
{
	if (_nextMove != "")
		return ;
}

void	chessAi::endGameMove(void)
{
	if (_nextMove != "")
		return ;
}

void	chessAi::randomMove(void)
{
	if (_nextMove != "")
		return ;
}

string	chessAi::getNextMove(void)
{
	_legalMoves = getLegalMoves();

	if (_newBoard.isCheckMateNextMove(true) == true)
		checkMateMove();
	else
	{
		if (_newBoard.isCheckMateNextMove(true, true) == true
			|| _newBoard.isCheck() == true || _newBoard.isAttacked() == true)
			defendMove();
		else
		{
			if (_newBoard.isEndGame() == true)
				endGameMove();
			else
			{
				attackMove();
				passiveMove();
			}
		}
	}
	randomMove();

	return (_nextMove);
}
