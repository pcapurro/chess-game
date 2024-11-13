#include "chessAi.hpp"

void	chessAi::checkMateMove(void)
{
	if (_nextMove != "")
		return ;
	
	cout << "checkmate move" << endl;
	_nextMove = getCheckMateMove();
}

void	chessAi::attackMove(void)
{
	if (_nextMove != "")
		return ;
	
	cout << "searching for attack move" << endl;
	_nextMove = getCounterStrike();

	if (_nextMove == "")
		cout << "no attack found" << endl;
	else
		cout << "attack found > " << _nextMove << endl;
}

void	chessAi::passiveMove(void)
{
	if (_nextMove != "")
		return ;

	cout << "passive move" << endl;
	_nextMove = getPassiveMove();
}

void	chessAi::defendMove(void)
{
	if (_nextMove != "")
		return ;

	if (isCheck() == true)
	{
		cout << "counter check" << endl;
		_nextMove = getCounterCheck();
		return ;
	}
	else
	{
		if (isDefeatNext() == true)
		{
			cout << "counter checkmate" << endl;
			_nextMove = getCounterCheckMate();

			if (_nextMove == "")
				cout << "no counter checkmate move found, attacking..." << endl, attackMove(), passiveMove();

			return ;
		}
	}

	cout << "ally defend move" << endl;
	if (isAllyAttacked() == true)
		_nextMove = getCounterProtect();

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
	_nextMove = getRandomMove();
}

string	chessAi::getNextMove(void)
{
	// sleep(1); //

	vector<string>	legalMoves;
	legalMoves = getLegalMoves();
	cout << "legal moves: " << endl;
	for (int i = 0; i != legalMoves.size(); i++)
		cout << legalMoves.at(i) << " ; ";
	cout << endl;

	isVictoryNextNext();

	// if (isCheck() == true)
	// 	defendMove();
	// else
	// {
	// 	if (isVictoryNext() == true)
	// 		checkMateMove();

	// 	if (isVictoryNextNext() == true)
	// 		attackMove();
	// 	else
	// 	{
	// 		if (isDefeatNext() == true || isAllyAttacked() == true)
	// 			defendMove();
	// 		else
	// 		{
	// 			if (isEndGame() == true)
	// 				endGameMove();
	// 			else
	// 			{
	// 				attackMove();
	// 				passiveMove();
	// 			}
	// 		}
	// 	}
		randomMove();
	// }

    if (_nextMove == "O-O" || _nextMove == "O-O-O")
    {
        if (_gameInfo._color == "white")
            _nextMove = "Ke1" + _nextMove;
        else
            _nextMove = "Ke8" + _nextMove;
    }

	return (_nextMove);
}
