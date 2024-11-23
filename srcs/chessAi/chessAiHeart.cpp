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

	if (_nextMove == "O-O" || _nextMove == "O-O-O")
	{
		if (_gameInfo._color == "white")
			_nextMove = "Ke1" + _nextMove;
		if (_gameInfo._color == "black")
			_nextMove = "Ke8" + _nextMove;
	}
}

void	chessAi::defendMove(void)
{
	if (_nextMove != "")
		return ;

	if (_check == true)
	{
		cout << "counter check" << endl;
		_nextMove = getCounterCheck();
		return ;
	}
	else if (_defeatNext == true)
	{
		cout << "counter checkmate" << endl;
		_nextMove = getCounterCheckMate();

		if (_nextMove == "")
			cout << "no counter checkmate move found, attacking..." << endl, attackMove(), passiveMove();

		return ;
	}

	if (_allyAttacked == true)
		cout << "ally defense" << endl, _nextMove = getCounterProtect();

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

void	chessAi::analyzeBoard(void)
{
	if (isCheck() == true)
		{ _check = true; return ; }
	
	if (isDefeatNext() == true)
		{ _defeatNext = true; return ; }

	if (isVictoryNextNext() == true)
		_victoryNextNext = true;

	if (isAllyAttacked() == true && isDefenseWorth() == true)
		_allyAttacked = true;
}

string	chessAi::getNextMove(void)
{
	// sleep(1); //
	
	analyzeBoard();

	if (_check == true) // v
		defendMove(); // x
	else
	{
		if (isVictoryNext() == true) // v
			checkMateMove(); // v
		else
		{
			if (_defeatNext == true || _allyAttacked == true)
				defendMove();
			else
			{
				if (isEndGame() == true)
					endGameMove();
				else
					attackMove(), passiveMove();
			}
		}
		randomMove();
	}

	cout << endl << "Legal moves: " << endl;
	vector<string>	legalMoves;
	legalMoves = getLegalMoves();
	for (int i = 0; i != legalMoves.size(); i++)
		cout << legalMoves.at(i) << " ; ";
	cout << endl << "-" << endl;

	cout << "solution => '" << _nextMove << "'" << endl;
	cout << endl;

	return (_nextMove);
}
