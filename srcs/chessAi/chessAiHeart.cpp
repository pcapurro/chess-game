#include "chessAi.hpp"

void	chessAi::checkMateMove(void)
{
	if (_nextMove != "")
		return ;
	
	cout << "checkmate move" << endl;
	_nextMove = _newBoard.getCheckMateMove();
}

void	chessAi::attackMove(void)
{
	if (_nextMove != "")
		return ;
	
	_nextMove = _newBoard.getCounterStrike();
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

	if (_newBoard.canItBeCheckMate(true) == true || _newBoard.isCheck() == true)
	{
		cout << "counter checkmate move" << endl;
		if (_newBoard.canItBeCheckMate(true) == true)
			{ _nextMove = _newBoard.getCounterCheckMate(); return ; }

		cout << "counter check move" << endl;
		if (_newBoard.isCheck() == true)
			{ _nextMove = _newBoard.getCounterCheck(); return ; }
	}

	cout << "ally defend move" << endl;
	if (_newBoard.isAttacked() == true)
		{ _nextMove = _newBoard.getCounterAttack(); return ; }
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
	_legalMoves = _newBoard.getLegalMoves();

	// sleep(1); //

	// if (_newBoard.canItBeCheckMate(true, true) == true)
	// 	checkMateMove();
	// else
	// {
	// 	if (_newBoard.canItBeCheckMate(true) == true
	// 		|| _newBoard.isCheck() == true || _newBoard.isAttacked() == true)
	// 		defendMove();
	// 	else
	// 	{
	// 		if (_newBoard.isEndGame() == true)
	// 			endGameMove();
	// 		else
	// 		{
	// 			attackMove();
	// 			passiveMove();
	// 		}
	// 	}
	// }
	randomMove();
	cout << "-" << endl;

	return (_nextMove);
}
