#include "chessAi.hpp"

void	chessAi::checkMateMove(void)
{
	if (_nextMove != "")
		return ;
	
	_nextMove = getCheckMateInOneMove();
}

void	chessAi::attackMove(void)
{
	if (_nextMove != "")
		return ;
	
	if (_gameInfo._turn > 1)
		_nextMove = getCounterStrike();

	if (_nextMove[0] == 'P' && _nextMove.size() == 6)
		_nextMove[5] = 'Q';
}

void	chessAi::passiveMove(void)
{
	if (_nextMove != "")
		return ;

	_nextMove = getPassiveMove();

	if (_nextMove == "O-O" || _nextMove == "O-O-O")
	{
		if (_gameInfo._color == "white")
			_nextMove = "Ke1" + _nextMove;
		if (_gameInfo._color == "black")
			_nextMove = "Ke8" + _nextMove;
	}

	if (_nextMove[0] == 'P' && _nextMove.size() == 6)
		_nextMove[5] = 'Q';
}

void	chessAi::defendMove(void)
{
	if (_nextMove != "")
		return ;

	if (_check == true)
	{
		_nextMove = getCounterCheckMate(0);
		return ;
	}
	else if (_defeatNext == true)
	{
		_nextMove = getCounterCheckMate(1);

		if (_nextMove == "")
			attackMove(), passiveMove();

		return ;
	}

	if (_allyAttacked == true)
		_nextMove = getCounterProtect();

	if (_checkNext == true && _allyAttacked == false && _nextMove == "")
		_nextMove = getCounterCheck();

	if (_nextMove[0] == 'P' && _nextMove.size() == 6)
		_nextMove[5] = 'Q';

	if (_nextMove == "")
		attackMove(), passiveMove();
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

	_nextMove = getRandomLogicMove();
	if (_nextMove != "")
		_nextMove = getRandomMove();
}

void	chessAi::analyzeBoard(void)
{
	if (isCheck() == true)
		_check = true;
	
	if (_check == false && isDefeatNext() == true)
		_defeatNext = true;

	if (_check == false && checkMateInOne() == true)
		_checkMateInOne = true;

	if (_checkMateInOne != true && checkMateInTwo() == true)
		_checkMateInTwo = true;

	if (isAllyAttacked() == true && isDefenseWorth() == true)
		_allyAttacked = true;

	// if (willBeCheck() == true)
	// 	_checkNext = true, cout << "checkNext detected" << endl;
	// else
	// 	cout << "no future check detected" << endl;
}

// string	chessAi::getNextMove(void)
// {
// 	// sleep(1);

// 	// cout << endl << "Legal moves: " << endl;
// 	// vector<string>	legalMoves;
// 	// legalMoves = getLegalMoves();
// 	// for (int i = 0; i != legalMoves.size(); i++)
// 	// 	cout << legalMoves.at(i) << " ; ";
// 	// cout << endl << "-" << endl << endl;
	
// 	analyzeBoard();

// 	if (_check == true)
// 		defendMove(); // x
// 	else
// 	{
// 		if (_checkMateInOne == true)
// 			checkMateMove(); // v
// 		else
// 		{
// 			if (_defeatNext == true || _allyAttacked == true
// 				|| _checkNext == true)
// 				defendMove(); // x
// 			else
// 			{
// 				attackMove(); // v
// 				passiveMove(); // v
// 			}
// 		}
// 	}
// 	randomMove(); // v

// 	cout << "answer > " << _nextMove << endl;

// 	return (_nextMove);
// }

vector<t_path>	chessAi::getPaths(void)
{
	vector<t_path>	paths;

	return (paths);
}

void	chessAi::evaluatePaths(vector<t_path> &paths)
{
	int		score;
	string	move;

	for (int i = 0; i != paths.size(); i++)
	{
		_simulation = true;
		for (int k = 0; k != paths.at(i).branch.size(); k++)
			move = paths.at(i).branch.at(k), tryMove(move);

		score = getScore(_gameInfo._color);
		paths.at(i).score = score;

		for (int k = paths.at(i).branch.size() - 1; k != -1; k--)
			move = paths.at(i).branch.at(k), undoMove(move);
		_simulation = false;
	}
}

string	chessAi::getNextMove(void)
{
	int				bestScore = 0;
	vector<t_path>	paths;

	paths = getPaths();
	evaluatePaths(paths);

	for (int i = 0; i != paths.size(); i++)
	{
		if (paths.at(i).score > bestScore)
		{
			_nextMove = paths.at(i).branch.at(0);
			bestScore = paths.at(i).score;
		}
	}

	cout << "> " << _nextMove << endl;

	return (_nextMove);
}
