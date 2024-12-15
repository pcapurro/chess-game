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
	string			move;
	string			answer;
	vector<string>	path;
	vector<string>	legalMoves;
	vector<string>	moves, newMoves;
	vector<string>	tested;

	vector<t_path>	paths;
	vector<t_path>	oldPaths;

	legalMoves = getLegalMoves();
	for (int i = 0; i != legalMoves.size(); i++)
	{
		string			move;

		move = legalMoves.at(i);
		if (count(move.begin(), move.end(), 'O') == 0)
			move = move.c_str() + 1;
		path.push_back(move);

		tryMove(move);
		answer = getBestAnswer();
		undoMove(move);
		path.push_back(answer);

		oldPaths.push_back({path, 0});
		path.clear();
	}

	// MAX_LEVEL = 4

	for (int i = 0; i != 1; i++)
	{
		if (paths.size() != 0)
			oldPaths = paths, paths.clear();

		for (int k = 0; k != oldPaths.size(); k++)
		{
			moves = oldPaths.at(k).branch;
		
			for (int j = 0; j != moves.size(); j++)
				tryMove(moves.at(j));
			
			legalMoves = getLegalMoves();

			for (int j = 0; j != legalMoves.size(); j++)
			{
				move = legalMoves.at(j);
				if (count(move.begin(), move.end(), 'O') == 0)
					move = move.c_str() + 1;

				newMoves = moves;
				newMoves.push_back(move);

				tryMove(move);
				answer = getBestAnswer();
				newMoves.push_back(answer);
				undoMove(move);

				paths.push_back({newMoves, 0});
			}

			for (int j = moves.size() - 1; j != -1; j--)
				undoMove(moves.at(j));
		}
	}

	cout << endl << "total of " << paths.size() << " branches detected." << endl;

	cout << "possible paths for " << _gameInfo._color << " >" << endl;
	for (int i = 0; i != paths.size(); i++)
	{
		cout << "– ";
		for (int k = 0; k != paths.at(i).branch.size(); k++)
			cout << paths.at(i).branch.at(k) << " > ";
		cout << endl;
	}

	sleep(500);
	exit(0);

	// oldPaths :

	// 0 {a2a3}, {\0}
	// 1 {a2a4}, {\0}
	// 2 {b2b3}, {\0}
	// 3 {b2b4}, {\0}
	// 4 {c2c3}, {\0}
	// 5 {c2c4}, {\0}
	// 6 {d2d3}, {\0}
	// 7 {d2d4}, {\0}
	// 8 {e2e3}, {\0}
	// 9 {e2e4}, {\0}
	// 10 {f2f3}, {\0}
	// 11 {f2f4}, {\0}

	// 12 {g2g3}, {\0}
	// 13 {g2g4}, {\0}
	// 14 {h2h3}, {\0}
	// 15 {h2h4}, {\0}

	// 16 {g1f3}, {\0}
	// 17 {g1h3}, {\0}
	// 18 {b1a3}, {\0}
	// 19 {b1c3}, {\0}

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
