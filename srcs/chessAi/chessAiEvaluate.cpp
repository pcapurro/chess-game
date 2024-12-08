#include "chessAi.hpp"

int		chessAi::evaluateMaterial(void)
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
				if (isAttacked(_board.at(i).coord) == true)
					attacked.push(_board.at(i).piece);
			}
			else
			{
				switchPlayers();
				if (isAttacked(_board.at(i).coord) == true)
					attacking.push(_board.at(i).piece);
				unSwitchPlayers();
			}
		}
	}

	if (attacked.size() != 0)
	{
		attacked = orderByValueRev(attacked);
		value -= getMaterialValue(attacked.top()->getType());
	}

	if (attacking.size() > 1)
	{
		attacking = orderByValueRev(attacking);
		attacking.pop();
		value += getMaterialValue(attacking.top()->getType());
	}

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
			&& _board.at(i).piece->getType() != 'K' && isAttacked(_board.at(i).coord) == false)
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

int		chessAi::evaluateAttack(void)
{
	int		value = 0;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != _gameInfo._color
			&& _board.at(i).piece->getType() != 'K' && isAttacked(_board.at(i).coord) == false)
		{
			switchPlayers();
			if (isAttacked(_board.at(i).coord) == true)
				value += (getMaterialValue(_board.at(i).piece->getType()) * 2);
			unSwitchPlayers();
		}
	}

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
		while (watchers.size() != 0)
		{
			if (isAttacked(watchers.top()->getCoord()) == false)
				value++;
			watchers.pop();
		}
	}

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
		while (watchers.size() != 0)
		{
			if (isAttacked(watchers.top()->getCoord()) == false)
				value++;
			watchers.pop();
		}
	}

	if (_gameInfo._color == "white")
	{
		if (_gameInfo._whiteCastled == true)
			value += 25;
		if (_gameInfo._whiteCastled == false && _gameInfo._whiteCastle == false)
			value -= 25;
	}

	if (_gameInfo._color == "black")
	{
		if (_gameInfo._blackCastled == true)
			value += 25;
		if (_gameInfo._blackCastled == false && _gameInfo._blackCastle == false)
			value -= 25;
	}

	return (value);
}

int		chessAi::evaluateMobility(void)
{
	int				value = 0;
	vector<string>	possibleMoves;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color
			&& isAttacked(_board.at(i).coord) == false)
		{
			if (_board.at(i).piece->getType() != 'K')
				value += (getPossibleTargets(_board.at(i).coord).size());
			else
				value += getPossibleTargets(_board.at(i).coord).size();
		}
	}

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
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color
			&& isAttacked(_board.at(i).coord) == false)
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
			&& isAttacked(_board.at(i).coord) == false)
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

	score += evaluateMaterial() * 10 * (normalCoeff + endCoeff);
	// cout << "– material > " << evaluateMaterial() * 10 << endl;

	score += evaluateDefense() * 4;
	// cout << "– defense > " << evaluateDefense() * 4 << endl;
	score += evaluateAttack() * 4;
	// cout << "– attack > " << evaluateAttack() * 4 << endl;
	score += evaluateThreats() * normalCoeff;
	// cout << "– threat > " << evaluateThreats() * normalCoeff << endl;

	score += evaluateKingControl() * 4;
	// cout << "– king control > " << evaluateKingControl() * 4 << endl;
	score += evaluateKingDefense() * 7;
	// cout << "– king defense > " << evaluateKingDefense() * 4 << endl;

	score += evaluatePromotion() * endCoeff;
	// cout << "– promotion > " << evaluatePromotion() * endCoeff << endl;

	score += evaluateMobility() * normalCoeff;
	// cout << "– mobility > " << evaluateMobility() * normalCoeff << endl;
	score += evaluatePawns() * 4 * endCoeff;
	// cout << "– pawns > " << evaluatePawns() * endCoeff << endl;

	if (_endGame == false)
	{
		score += evaluateCenter() * normalCoeff;
		// cout << "– center > " << evaluateCenter() * normalCoeff << endl;
		score += evaluateDev() * normalCoeff;
		// cout << "– global dev > " << evaluateDev() * normalCoeff << endl;
	}

	return (score);
}

void	chessAi::evaluateBoard(void)
{
	if (_endGame == false && isEndGame() == true)
		_endGame = true, _normalGame = false;

	if (_gameInfo._color == "white")
		cout << "white score > " << endl, _whiteScore = getScore(), cout << "total > " << _whiteScore << endl;
	else
		cout << "black score > " << endl, _blackScore = getScore(), cout << "total > " << _blackScore << endl;

	cout << endl;

	switchPlayers();

	if (_gameInfo._color == "white")
		cout << "white score > " << endl, _whiteScore = getScore(), cout << "total > " << _whiteScore << endl;
	else
		cout << "black score > " << endl, _blackScore = getScore(), cout << "total > " << _blackScore << endl;

	unSwitchPlayers();	
}
