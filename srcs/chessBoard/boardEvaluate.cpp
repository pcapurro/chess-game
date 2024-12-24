#include "chessBoard.hpp"

int		chessBoard::evaluateMaterial(void)
{
	int			value = 0;
	int			enemyMaterial = 0;
	stack<cP *>	attacked;
	stack<cP *>	attacking;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getType() != 'K')
		{
			if (_board.at(i).piece->getColor() == _gameInfo._color)
				value += getMaterialValue(_board.at(i).piece->getType());
			else
				enemyMaterial += getMaterialValue(_board.at(i).piece->getType());
		}
	}

	value += 39 - enemyMaterial;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getType() != 'K')
		{
			if (_board.at(i).piece->getColor() == _gameInfo._color)
			{
				if (isSafe(_board.at(i).coord) == false)
					attacked.push(_board.at(i).piece);
			}
			else
			{
				switchPlayers();
				if (isSafe(_board.at(i).coord) == false)
					attacking.push(_board.at(i).piece);
				unSwitchPlayers();
			}
		}
	}

	if (attacked.size() != 0)
	{
		attacked = orderByValue(attacked);
		value -= getMaterialValue(attacked.top()->getType());
	}

	if (value < 0)
		value = 0;

	return (value);
}

int		chessBoard::evaluateDefense(void)
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

	return (value);
}

int		chessBoard::evaluateAttack(void)
{
	int				value = 0;
	vector<string>	boardCoords;

	boardCoords = getPiecesCoords();
	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color
			&& _board.at(i).piece->getType() != 'K' && isSafe(_board.at(i).coord) == true)
		{
			for (int k = 0; k != 64; k++)
			{
				if (_board.at(k).piece != NULL && _board.at(k).piece->getColor() != _gameInfo._color
					&& _board.at(i).piece->isOnMyWay(_board.at(k).coord, boardCoords, 0, _gameInfo._enPassantDest) == true)
					value++;
			}
		}
	}

	return (value);
}

int		chessBoard::evaluateKingControl(void)
{
	int				value = 0;
	string			coord, kingCoords;
	vector<string>	kingWays;
	stack<cP *>		watchers;

	if (_gameInfo._check == false && checkMateInOne() == true)
		value += 50;

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
		while (watchers.size() != 0)
		{
			if (isSafe(watchers.top()->getCoord()) == true)
				value++;
			watchers.pop();
		}
	}

	return (value);
}

int		chessBoard::evaluateKingDefense(void)
{
	int		value = 0;

	if (_gameInfo._check == false && isDefeatNext() == true)
        value -= 21000;

	if (_gameInfo._color == "white" && _gameInfo._whiteCastled == true)
		value += 15;

	if (_gameInfo._color == "black" && _gameInfo._blackCastled == true)
		value += 15;

	if (value != 0 || isEndGame() == true)
	{
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
			while (watchers.size() != 0)
			{
				if (isSafe(watchers.top()->getCoord()) == true)
					value++;
				watchers.pop();
			}
		}
	}

	return (value);
}

int		chessBoard::evaluateMobility(void)
{
	int				value = 0;
	vector<string>	possibleMoves;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color
			&& isSafe(_board.at(i).coord) == true)
		{
			if (_board.at(i).piece->getType() != 'K')
				value += (getPossibleTargets(_board.at(i).coord).size());
			else
				value += getPossibleTargets(_board.at(i).coord).size();
		}
	}

	return (value);
}

int		chessBoard::evaluatePromotion(void)
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

	return (value);
}

int		chessBoard::evaluatePawns(void)
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

	return (value);
}

int		chessBoard::evaluateCenter(void)
{
	int				value = 0;
	string			targets[] = {"e4", "e5", "d4", "d5"};
	vector<string>	boardCoords;

	boardCoords = getPiecesCoords();
	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color
			&& isSafe(_board.at(i).coord) == true)
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
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color
			&& isSafe(_board.at(i).coord) == true)
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

	return (value);
}

int		chessBoard::evaluateDev(void)
{
	int		value = 0;
	int		atValue;
    char    nb1, nb2;

	_gameInfo._color == "white" ? nb1 = '1', nb2 = '2' : nb1 = '8', nb2 = '7';

	atValue = getAtValue(string(1, 'b') + nb1);
	if (_board.at(atValue).piece == NULL || _board.at(atValue).piece->getMoves() != 0)
		value += 8;
	
	atValue = getAtValue(string(1, 'g') + nb1);
	if (_board.at(atValue).piece == NULL || _board.at(atValue).piece->getMoves() != 0)
		value += 8;

	atValue = getAtValue(string(1, 'c') + nb1);
	if (_board.at(atValue).piece == NULL || _board.at(atValue).piece->getMoves() != 0)
		value += 8;
	
	atValue = getAtValue(string(1, 'f') + nb1);
	if (_board.at(atValue).piece == NULL || _board.at(atValue).piece->getMoves() != 0)
		value += 8;

	atValue = getAtValue(string(1, 'd') + nb2);
	if (_board.at(atValue).piece == NULL || _board.at(atValue).piece->getType() != 'P')
		value += 16;

	atValue = getAtValue(string(1, 'e') + nb2);
	if (_board.at(atValue).piece == NULL || _board.at(atValue).piece->getType() != 'P')
		value += 16;

	return (value);
}

int		chessBoard::getScore(const string color)
{
	int		score = 0;
	int		normalCoeff = 1;
	int		endCoeff = 1;
	bool	colorSwitch = false;

	isEndGame() == false ? normalCoeff = 4 : endCoeff = 4;

	if (_gameInfo._color != color)
		switchPlayers(), colorSwitch = true;

	score += evaluateKingControl() * (normalCoeff + endCoeff);
	// cout << "– king control > " << evaluateKingControl() * (normalCoeff + endCoeff) << endl;
	score += evaluateKingDefense() * (normalCoeff + endCoeff);
	// cout << "– king defense > " << evaluateKingDefense() * (normalCoeff + endCoeff) << endl;

	score += evaluateMaterial() * (normalCoeff + endCoeff);
	// cout << "– material > " << evaluateMaterial() * 10 * (normalCoeff + endCoeff) << endl;

	score += evaluateDefense() * 4;
	// cout << "– defense > " << evaluateDefense() * 4 << endl;
	score += evaluateAttack() * 4;
	// cout << "– attack > " << evaluateAttack() * 4 << endl;

	score += evaluatePromotion() * (normalCoeff + endCoeff);
	// cout << "– promotion > " << evaluatePromotion() * (normalCoeff + endCoeff) << endl;

	score += evaluateMobility() * 1;
	// cout << "– mobility > " << evaluateMobility() * 1 << endl;
	score += evaluatePawns() * 4 * endCoeff;
	// cout << "– pawns > " << evaluatePawns() * 4 * endCoeff << endl;

	if (normalCoeff == 4)
	{
		score += evaluateCenter() * normalCoeff;
		// cout << "– center > " << evaluateCenter() * normalCoeff << endl;
		score += evaluateDev() * normalCoeff;
		// cout << "– global dev > " << evaluateDev() * normalCoeff << endl;
	}

	if (colorSwitch == true)
		unSwitchPlayers();

	return (score);
}
