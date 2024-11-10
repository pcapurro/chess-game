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

	if (_newBoard.isCheck() == true)
	{
		cout << "counter check" << endl;
		_nextMove = _newBoard.getCounterCheck();
		return ;
	}
	else
	{
		if (_newBoard.canItBeCheckMateNext() == true)
		{
			cout << "counter checkmate" << endl;
			_nextMove = _newBoard.getCounterCheckMate();

			if (_nextMove == "")
				cout << "no counter checkmate move found, attacking..." << endl, attackMove(), passiveMove();

			return ;
		}
	}

	cout << "ally defend move" << endl;
	if (_newBoard.isSomethingAttacked() == true)
		_nextMove = _newBoard.getCounterProtect();

	if (_nextMove == "")
		attackMove(), passiveMove();
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
	_nextMove = _newBoard.getRandomMove();
}

string	chessAi::getNextMove(void)
{
	// sleep(1); //

	vector<string>	legalMoves;
	legalMoves = _newBoard.getLegalMoves();
	cout << "legal moves: " << endl;
	for (int i = 0; i != legalMoves.size(); i++)
		cout << legalMoves.at(i) << " ; ";
	cout << endl;

	if (_newBoard.isCheck() == true)
		defendMove();
	else
	{
		if (_newBoard.canItBeCheckMateNow() == true)
			checkMateMove();
		else
		{
			if (_newBoard.canItBeCheckMateNext() == true
				|| _newBoard.isCheck() == true || _newBoard.isSomethingAttacked() == true)
				defendMove();
			// else
			// {
			// 	if (_newBoard.isEndGame() == true)
			// 		endGameMove();
			// 	else
			// 	{
			// 		attackMove();
			// 		passiveMove();
			// 	}
			// }
		}
		randomMove();
	}

	return (_nextMove);
}
