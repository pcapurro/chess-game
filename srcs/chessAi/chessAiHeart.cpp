#include "chessAi.hpp"

void	chessAi::checkMateMove(void)
{
	if (_nextMove != "")
		return ;
	
	cout << "checkmate move" << endl;
	_nextMove = getCheckMateInOneMove();
}

void	chessAi::attackMove(void)
{
	if (_nextMove != "")
		return ;
	
	if (_gameInfo._turn > 1)
	{
		cout << "searching for attack move" << endl;
		_nextMove = getCounterStrike();

		if (_nextMove == "")
			cout << "no attack found" << endl;
		else
			cout << "attack found > " << _nextMove << endl;
	}
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
		_nextMove = getCounterCheckMate(0);
		return ;
	}
	else if (_defeatNext == true)
	{
		cout << "counter checkmate" << endl;
		_nextMove = getCounterCheckMate(1);

		if (_nextMove == "")
			cout << "no counter checkmate move found, attacking..." << endl, attackMove(), passiveMove();

		return ;
	}

	if (_allyAttackedNext == true)
		cout << "ally next defense" << endl, _nextMove = getCounterNextAttack();

	if (_allyAttacked == true && _nextMove == "")
		cout << "ally defense" << endl, _nextMove = getCounterProtect();

	if (_allyDoubleAttacked == true && _nextMove == "")
		cout << "ally double attacked defense" << endl, _nextMove = getCounterDoubleAttack();

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

	_nextMove = getRandomLogicMove();
	if (_nextMove != "")
		_nextMove = getRandomMove();
}

void	chessAi::analyzeBoard(void)
{
	if (isCheck() == true)
		_check = true, cout << "check detected" << endl;
	
	if (isDefeatNext() == true)
		_defeatNext = true, cout << "defeatNext detected" << endl;

	if (checkMateInOne() == true)
		_checkMateInOne = true, cout << "checkMateInOne detected" << endl;

	if (checkMateInTwo() == true && _checkMateInOne != true)
		_checkMateInTwo = true, cout << "checkMateInTwo detected" << endl;

	if (willAllyBeAttacked() == true && willDefenseBeWorth() == true)
		_allyAttackedNext = true, cout << "allyAttackedNext detected" << endl;

	if (isAllyAttacked() == true && isDefenseWorth() == true)
		_allyAttacked = true, cout << "allyAttacked detected" << endl;

	if (isAllyDoubleAttacked() == true)
		_allyDoubleAttacked = true, cout << "allyDoubleAttacked detected" << endl;
}

string	chessAi::getNextMove(void)
{
	// sleep(1);

	cout << endl << "Legal moves: " << endl;
	vector<string>	legalMoves;
	legalMoves = getLegalMoves();
	for (int i = 0; i != legalMoves.size(); i++)
		cout << legalMoves.at(i) << " ; ";
	cout << endl << "-" << endl << endl;
	
	analyzeBoard();

	if (_check == true)
		defendMove(); // x
	else
	{
		if (_checkMateInOne == true)
			checkMateMove(); // v
		else
		{
			if (_defeatNext == true || _allyAttacked == true
				|| _allyDoubleAttacked == true || _allyAttackedNext == true)
				defendMove(); // x
			else
			{
				attackMove(); // v
				passiveMove(); // v
			}
		}
	}
	randomMove(); // v

	cout << "solution => '" << _nextMove << "'" << endl;

	return (_nextMove);
}
