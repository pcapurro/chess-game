#include "ChessBoard.hpp"

int	ChessBoard::evaluateMaterial(const bool colorSwitch)
{
	int			value = 0;
	int			enemyMaterial = 0;
	stack<cP*>	attacked;
	stack<cP*>	attacking;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != nullptr && _board.at(i).piece->getType() != 'K')
		{
			if (_board.at(i).piece->getColor() == _gameInfo.color)
				value += getMaterialValue(_board.at(i).piece->getType()) * 2;
			else
				enemyMaterial += getMaterialValue(_board.at(i).piece->getType()) * 2;
		}
	}

	value += 78 - enemyMaterial;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != nullptr && _board.at(i).piece->getType() != 'K')
		{
			if (_board.at(i).piece->getColor() == _gameInfo.color)
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

	if (attacking.size() != 0)
	{
		attacking = orderByValue(attacking);
		if (colorSwitch == false)
			value += getMaterialValue(attacking.top()->getType()) * 2;
		else
		{
			attacking.pop();
			if (attacking.size() != 0)
				value += getMaterialValue(attacking.top()->getType()) * 2;
		}
	}

	if (attacked.size() != 0)
	{
		attacked = orderByValue(attacked);
		if (colorSwitch == true)
			value -= getMaterialValue(attacked.top()->getType()) * 2;
		else
		{
			attacked.pop();
			if (attacked.size() != 0)
				value -= getMaterialValue(attacked.top()->getType()) * 2;
		}
	}

	if (value < 0)
		value = 0;

	return (value);
}

int		ChessBoard::evaluateDefense(void)
{
	int	value = 0;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != nullptr && _board.at(i).piece->getColor() == _gameInfo.color \
			&& _board.at(i).piece->getType() != 'K')
		{
			if (isSafe(_board.at(i).coord) == true)
				value += getMaterialValue(_board.at(i).piece->getType());
		}
	}

	return (value);
}

int		ChessBoard::evaluateAttack(void)
{
	int				value = 0;
	vector<string>	boardCoords;

	boardCoords = getPiecesCoords();
	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != nullptr && _board.at(i).piece->getColor() == _gameInfo.color \
			&& _board.at(i).piece->getType() != 'K' && isSafe(_board.at(i).coord) == true)
		{
			for (int k = 0; k != 64; k++)
			{
				if (_board.at(k).piece != nullptr && _board.at(k).piece->getColor() != _gameInfo.color \
					&& _board.at(i).piece->isOnMyWay(_board.at(k).coord, boardCoords, 0, _gameInfo.enPassantDest) == true)
					value++;
			}
		}
	}

	return (value);
}

int		ChessBoard::evaluateKingControl(const bool colorSwitch)
{
	int				value = 0;
	string			coord, kingCoords;
	vector<string>	kingWays;
	stack<cP*>		watchers;

	if (_gameInfo.check == false && checkMateInOne() == true)
		colorSwitch == true ? value += 50 : value += 42000;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != nullptr && _board.at(i).piece->getColor() != _gameInfo.color)
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

	for (size_t i = 0; i != kingWays.size(); i++)
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

int		ChessBoard::evaluateKingDefense(const bool colorSwitch)
{
	int		value = 0;

	if (_gameInfo.check == false && isDefeatNext() == true)
		colorSwitch == true ? value -= 42000 : value += 50;

	if (_gameInfo.color == "white" && _gameInfo.whiteCastled == true)
		value += 15;

	if (_gameInfo.color == "black" && _gameInfo.blackCastled == true)
		value += 15;

	if (value != 0 || isEndGame() == true)
	{
		string			coord, kingCoords;
		vector<string>	kingWays;
		stack<cP*>		watchers;

		for (int i = 0; i != 64; i++)
		{
			if (_board.at(i).piece != nullptr && _board.at(i).piece->getColor() == _gameInfo.color)
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

		for (size_t i = 0; i != kingWays.size(); i++)
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

int		ChessBoard::evaluateMobility(void)
{
	int				value = 0;
	vector<string>	possibleMoves;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != nullptr && _board.at(i).piece->getColor() == _gameInfo.color \
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

int		ChessBoard::evaluatePromotion(void)
{
	int		value = 0;
	string	next;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != nullptr && _board.at(i).piece->getColor() == _gameInfo.color)
		{
			if (_board.at(i).piece->getType() == 'P' && isSafe(_board.at(i).coord) == true)
			{
				if (_gameInfo.color == "white")
					next = _board.at(i).coord, next[1] = next[1] + 1;
				if (_gameInfo.color == "black")
					next = _board.at(i).coord, next[1] = next[1] - 1;

				if (_board.at(getAtValue(next)).piece == nullptr \
					|| _board.at(getAtValue(next)).piece->getColor() == _gameInfo.color \
					|| _board.at(getAtValue(next)).piece->getType() != 'P')
					value += _board.at(i).piece->getMoves();
			}
		}
	}

	return (value);
}

int		ChessBoard::evaluatePawns(void)
{
	int			value = 0;
	stack<cP*>	watchers;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != nullptr && _board.at(i).piece->getColor() == _gameInfo.color)
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

int		ChessBoard::evaluateCenter(void)
{
	int				value = 0;
	string			targets[] = {"e4", "e5", "d4", "d5"};
	vector<string>	boardCoords;

	boardCoords = getPiecesCoords();
	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != nullptr && _board.at(i).piece->getColor() == _gameInfo.color \
			&& isSafe(_board.at(i).coord) == true)
		{
			for (int k = 0; k != 4; k++)
			{
				if (_board.at(i).piece->isOnMyWay(targets[k], boardCoords, 1, _gameInfo.enPassantDest) == true)
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
		if (_board.at(i).piece != nullptr && _board.at(i).piece->getColor() == _gameInfo.color \
			&& isSafe(_board.at(i).coord) == true)
		{
			if (_board.at(i).coord == "e4" || _board.at(i).coord == "e5" \
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

int		ChessBoard::evaluateDev(void) const
{
	int		value = 0;
	int		atValue;
	char	nb1, nb2;

	_gameInfo.color == "white" ? nb1 = '1', nb2 = '2' : nb1 = '8', nb2 = '7';

	atValue = getAtValue({'b', nb1});
	if (_board.at(atValue).piece == nullptr || _board.at(atValue).piece->getMoves() != 0)
		value += 8;
	
	atValue = getAtValue({'g', nb1});
	if (_board.at(atValue).piece == nullptr || _board.at(atValue).piece->getMoves() != 0)
		value += 8;

	atValue = getAtValue({'c', nb1});
	if (_board.at(atValue).piece == nullptr || _board.at(atValue).piece->getMoves() != 0)
		value += 8;
	
	atValue = getAtValue({'f', nb1});
	if (_board.at(atValue).piece == nullptr || _board.at(atValue).piece->getMoves() != 0)
		value += 8;

	atValue = getAtValue({'d', nb2});
	if (_board.at(atValue).piece == nullptr || _board.at(atValue).piece->getType() != 'P')
		value += 16;

	atValue = getAtValue({'e', nb2});
	if (_board.at(atValue).piece == nullptr || _board.at(atValue).piece->getType() != 'P')
		value += 16;

	return (value);
}

int		ChessBoard::getScore(const string color)
{
	int		score = 0;
	int		normalCoeff = 1;
	int		endCoeff = 1;
	bool	colorSwitch = false;

	isEndGame() == false ? normalCoeff = 4 : endCoeff = 4;

	if (_gameInfo.color != color)
		switchPlayers(), colorSwitch = true;

	score += evaluateKingControl(colorSwitch) * (normalCoeff + endCoeff);
	score += evaluateKingDefense(colorSwitch) * (normalCoeff + endCoeff);

	score += evaluateMaterial(colorSwitch) * ((normalCoeff * 2) + endCoeff);

	score += evaluateDefense() * 4;
	score += evaluateAttack() * 4;

	score += evaluatePromotion() * (normalCoeff + endCoeff);

	score += evaluateMobility() * 1;
	score += evaluatePawns() * 4 * endCoeff;

	if (normalCoeff == 4)
	{
		score += evaluateCenter() * normalCoeff;
		score += evaluateDev() * normalCoeff;
	}

	if (colorSwitch == true)
		unSwitchPlayers();

	return (score);
}
