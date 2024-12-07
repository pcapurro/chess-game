#include "chessAi.hpp"

int		chessAi::evaluateMaterial(void)
{
	int	value = 0;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color)
			value += getMaterialValue(_board.at(i).piece->getType());
	}

	return (value);
}

int		chessAi::evaluateDefense(void)
{
	int	value = 0;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color)
		{
			if (isSafe(_board.at(i).coord) == true)
				value += getMaterialValue(_board.at(i).piece->getType());
		}
	}

	return (value);
}

int		chessAi::evaluateAttack(void)
{
	int	value = 0;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != _gameInfo._color)
		{
			if (isAttacked(_board.at(i).coord) == true)
				value += getMaterialValue(_board.at(i).piece->getType());
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

		for (; watchers.size() != 0; watchers.pop())
			value += (getMaterialValue(watchers.top()->getType()));
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
		for (; watchers.size() != 0; watchers.pop())
			value += getMaterialValue(watchers.top()->getType());
	}

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
				value += ((getPossibleTargets(_board.at(i).coord).size()) * _board.at(i).piece->getType());
			else
				value += getPossibleTargets(_board.at(i).coord).size();
		}
	}

	return (value);
}

int		chessAi::evaluatePromotion(void)
{
	int		value = 0;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color)
		{
			if (_board.at(i).piece->getType() == 'P' && isSafe(_board.at(i).coord) == true)
				value += _board.at(i).piece->getMoves();
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

	return (value);
}

int		chessAi::evaluateDev(void)
{
	int		value = 0;
    char    nb;

	_gameInfo._color == "white" ? nb = '1' : nb = '8';

	if (_board.at(getAtValue("b" + nb)).piece != NULL && _board.at(getAtValue("b" + nb)).piece->getMoves() == 0)
		value += 3;
	if (_board.at(getAtValue("g" + nb)).piece != NULL && _board.at(getAtValue("g" + nb)).piece->getMoves() == 0)
		value += 3;

	if (_board.at(getAtValue("c" + nb)).piece != NULL && _board.at(getAtValue("c" + nb)).piece->getMoves() == 0)
		value += 3;
	if (_board.at(getAtValue("f" + nb)).piece != NULL && _board.at(getAtValue("f" + nb)).piece->getMoves() == 0)
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

	return (value);
}

int		chessAi::getScore(void)
{
	int	score = 0;

	score += evaluateMaterial();

	score += evaluateDefense();
	score += evaluateAttack();

	score += evaluateKingControl();
	score += evaluateKingDefense();

	score += evaluateMobility();
	score += evaluatePromotion();
	score += evaluatePawns();

	score += evaluateCenter();
	score += evaluateDev();

	return (score);
}

void	chessAi::evaluateBoard(void)
{
	int	whiteScore = 0;
	int	blackScore = 0;

	_gameInfo._color = "white";
	whiteScore = getScore();

	_gameInfo._color = "black";
	blackScore = getScore();

	cout << "white score > " << whiteScore << endl;
	cout << "black score > " << blackScore << endl;
}

// – évaluation –

// – matériel v 
// (valeur totale)

// – protection v
// (nb de pièces protégées)

// – attaques v
// (nb d'attaques possible)

// – contrôle du roi adverse v
// (visée alliée case alentours)

// – mobilité v
// (nb de coups possible pour chaque pièces)

// – promotion v
// (pions proches)

// – contrôle du centre v
// (visée du centre = e4/e5/d4/d5)

// – positionnement v
// (occupation du centre = e4/e5/d4/d5)

// – sécurité du roi allié v
// (visée adverse case alentours)

// – structure de pions v
// (doublés/isolés)
// (défendus/structurés/en avant)

// – développement v
// (cavaliers/fous/roque)