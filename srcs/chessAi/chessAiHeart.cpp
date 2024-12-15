#include "chessAi.hpp"

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
		if (move[0] != 'O')
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
				if (move[0] != 'O')
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
