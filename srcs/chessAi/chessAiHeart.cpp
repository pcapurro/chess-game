#include "chessAi.hpp"

void	chessAi::checkMateMove(void)
{
	if (_nextMove != "")
		return ;
	
	cout << "checkmate move" << endl;
	_nextMove = _newBoard._checkMateMove;
}

void	chessAi::attackMove(void)
{
	if (_nextMove != "")
		return ;
	
	cout << "attack move" << endl;
}

void	chessAi::passiveMove(void)
{
	if (_nextMove != "")
		return ;

	cout << "passive move" << endl;
}

void	chessAi::defendMove(void)
{
	if (_nextMove != "")
		return ;

	if (_newBoard.isCheck() == true)
		cout << "counter check move" << endl;
	if (_newBoard.isCheckMateNextMove(true) == true)
		cout << "counter checkmate move" << endl;
	if (_newBoard.isAttacked() == true)
		cout << "ally defend move" << endl;
}

void	chessAi::endGameMove(void)
{
	if (_nextMove != "")
		return ;

	cout << "end game move" << endl;
}

void	chessAi::randomMove(void)
{
	if (_nextMove != "")
		return ;

	cout << "random move" << endl;

	int	value = rand() % _legalMoves.size();
	_nextMove = _legalMoves.at(value);
}

string	chessAi::getNextMove(void)
{
	_legalMoves = getLegalMoves();

	// sleep(1); //

	if (_newBoard.isCheckMateNextMove(true, true) == true)
		checkMateMove();
	else
	{
		if (_newBoard.isCheckMateNextMove(true) == true
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
	cout << "-" << endl;

	return (_nextMove);
}
