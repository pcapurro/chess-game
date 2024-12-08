#include "chessAi.hpp"

int		chessAi::evaluateMaterial(void)
{
	int			value = 0;
	stack<cP *>	attacked;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color
			&& _board.at(i).piece->getType() != 'K')
		{
			value += getMaterialValue(_board.at(i).piece->getType());

			if (isAttacked(_board.at(i).coord) == true)
				attacked.push(_board.at(i).piece);
		}
	}

	if (attacked.size() != 0)
	{
		attacked = orderByValueRev(attacked);
		value -= getMaterialValue(attacked.top()->getType());
	}

	// cout << "material > " << value << endl;

	return (value);
}

int		chessAi::evaluateDefense(void)
{
	int	value = 0;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color
			&& _board.at(i).piece->getType() != 'K')
		{
			if (isSafe(_board.at(i).coord) == true)
				value += getMaterialValue(_board.at(i).piece->getType());
		}
	}

	// cout << "defense > " << value << endl;

	return (value);
}

int		chessAi::evaluateThreats(void)
{
	int				value = 0;
	vector<string>	boardCoords;

	boardCoords = getPiecesCoords();
	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color
			&& _board.at(i).piece->getType() != 'K')
		{
			for (int k = 0; k != 64; k++)
			{
				if (_board.at(k).piece != NULL && _board.at(k).piece->getColor() != _gameInfo._color
					&& _board.at(i).piece->isOnMyWay(_board.at(k).coord, boardCoords, 0, _gameInfo._enPassantDest) == true)
					value++;
			}
		}
	}

	// cout << "threats > " << value << endl;

	return (value);
}

int		chessAi::evaluateAttack(void)
{
	int		value = 0;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != _gameInfo._color
			&& _board.at(i).piece->getType() != 'K')
		{
			switchPlayers();
			if (isAttacked(_board.at(i).coord) == true)
				value += (getMaterialValue(_board.at(i).piece->getType()) * 2);
			unSwitchPlayers();
		}
	}

	// cout << "attack > " << value << endl;

	return (value);
}

int		chessAi::evaluateKingControl(void)
{
	int				value = 0;
	string			coord, kingCoords;
	vector<string>	kingWays;
	stack<cP *>		watchers;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != _gameInfo._color)
		{
			if (_board.at(i).piece->getType() == 'K')
				{ kingCoords = _board.at(i).coord; break ; }
		}
	}

    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            coord = "abcdefgh"[i] + to_string(k + 1);
			if (King("white", kingCoords).isOnMyWay(coord) == true)
				kingWays.push_back(coord);
        }
    }

	for (int i = 0; i != kingWays.size(); i++)
	{
		watchers = getWatchers(kingWays.at(i));
		value += watchers.size();
	}
	
	// cout << "enemy control > " << value << endl;

	return (value);
}

int		chessAi::evaluateKingDefense(void)
{
	int				value = 0;
	string			coord, kingCoords;
	vector<string>	kingWays;
	stack<cP *>		watchers;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color)
		{
			if (_board.at(i).piece->getType() == 'K')
				{ kingCoords = _board.at(i).coord; break ; }
		}
	}

    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            coord = "abcdefgh"[i] + to_string(k + 1);
			if (King("white", kingCoords).isOnMyWay(coord) == true)
				kingWays.push_back(coord);
        }
    }

	for (int i = 0; i != kingWays.size(); i++)
	{
		watchers = getWatchers(kingWays.at(i));
		value += watchers.size();
	}

	// cout << "king defense > " << value << endl;

	return (value);
}

int		chessAi::evaluateMobility(void)
{
	int				value = 0;
	vector<string>	possibleMoves;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color)
		{
			if (_board.at(i).piece->getType() != 'K')
				value += (getPossibleTargets(_board.at(i).coord).size());
			else
				value += getPossibleTargets(_board.at(i).coord).size();
		}
	}

	// cout << "mobility > " << value << endl;

	return (value);
}

int		chessAi::evaluatePromotion(void)
{
	int		value = 0;
	string	next;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color)
		{
			if (_board.at(i).piece->getType() == 'P' && isSafe(_board.at(i).coord) == true)
			{
				if (_gameInfo._color == "white")
					next = _board.at(i).coord, next[1] = next[1] + 1;
				if (_gameInfo._color == "black")
					next = _board.at(i).coord, next[1] = next[1] - 1;

				if (_board.at(getAtValue(next)).piece == NULL || _board.at(getAtValue(next)).piece->getColor() == _gameInfo._color
					|| _board.at(getAtValue(next)).piece->getType() != 'P')
					value += _board.at(i).piece->getMoves();
			}
		}
	}

	// cout << "promotion > " << value << endl;

	return (value);
}

int		chessAi::evaluatePawns(void)
{
	int			value = 0;
	stack<cP *>	watchers;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color)
		{
			if (_board.at(i).piece->getType() == 'P' && isSafe(_board.at(i).coord) == true)
			{
				watchers = getWatchers(_board.at(i).coord);
				while (watchers.size() != 0)
				{
					if (watchers.top()->getType() == 'P')
						value++;
					watchers.pop();
				}
			}
		}
	}

	// cout << "pawns dev > " << value << endl;

	return (value);
}

int		chessAi::evaluateCenter(void)
{
	int				value = 0;
	string			targets[] = {"e4", "e5", "d4", "d5"};
	vector<string>	boardCoords;

	boardCoords = getPiecesCoords();
	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color)
		{
			for (int k = 0; k != 4; k++)
			{
				if (_board.at(i).piece->isOnMyWay(targets[k], boardCoords, 1, _gameInfo._enPassantDest) == true)
				{
					if (_board.at(i).piece->getType() != 'K')
						value += getMaterialValue(_board.at(i).piece->getType());
					else
						value++;
				}
			}
		}
	}

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color)
		{
			if (_board.at(i).coord == "e4" || _board.at(i).coord == "e5"
				|| _board.at(i).coord == "d4" || _board.at(i).coord == "d5")
			{
				if (_board.at(i).piece->getType() != 'K')
					value += getMaterialValue(_board.at(i).piece->getType());
				else
					value++;

				if (isSafe(_board.at(i).coord) == true)
					value++;
			}
		}
	}

	// cout << "center control > " << value << endl;

	return (value);
}

int		chessAi::evaluateDev(void)
{
	int		value = 0;
	int		atValue;
    char    nb;

	_gameInfo._color == "white" ? nb = '1' : nb = '8';

	atValue = getAtValue(string(1, 'b') + nb);
	if (_board.at(atValue).piece == NULL || _board.at(atValue).piece->getMoves() != 0)
		value += 3;
	
	atValue = getAtValue(string(1, 'g') + nb);
	if (_board.at(atValue).piece == NULL || _board.at(atValue).piece->getMoves() != 0)
		value += 3;

	atValue = getAtValue(string(1, 'c') + nb);
	if (_board.at(atValue).piece == NULL || _board.at(atValue).piece->getMoves() != 0)
		value += 3;
	
	atValue = getAtValue(string(1, 'f') + nb);
	if (_board.at(atValue).piece == NULL || _board.at(atValue).piece->getMoves() != 0)
		value += 3;
	
	if (_gameInfo._color == "white")
	{
		if (_gameInfo._whiteCastled == true)
			value + value + 5;
	}

	if (_gameInfo._color == "black")
	{
		if (_gameInfo._blackCastled == true)
			value + value + 5;
	}

	// cout << "global dev > " << value << endl;

	return (value);
}

int		chessAi::getScore(void)
{
	int	score = 0;
	int	normalCoeff = 1;
	int	endCoeff = 1;

	if (_normalGame == true)
		normalCoeff = 4;
	if (_endGame == true)
		endCoeff = 4;

	score += evaluateMaterial() * 10;

	score += evaluateDefense() * 4;
	score += evaluateAttack() * 4;
	score += evaluateThreats() * normalCoeff;

	score += evaluateKingControl() * 4;
	score += evaluateKingDefense() * 4;

	score += evaluatePromotion() * endCoeff;

	score += evaluateMobility() * normalCoeff;
	score += evaluatePawns() * endCoeff;

	if (_endGame == false)
	{
		score += evaluateCenter() * normalCoeff;
		score += evaluateDev() * normalCoeff;
	}

	return (score);
}

void	chessAi::evaluateBoard(void)
{
	if (_endGame == false && isEndGame() == true)
		_endGame = true, _normalGame = false;

	if (_gameInfo._color == "white")
		_whiteScore = getScore();
	else
		_blackScore = getScore();

	switchPlayers();

	if (_gameInfo._color == "white")
		_whiteScore = getScore();
	else
		_blackScore = getScore();

	unSwitchPlayers();	
}
