#include "chessAi.hpp"

int		chessAi::evaluateMaterial(void)
{
	int	value = 0;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color)
			value = value + getMaterialValue(_board.at(i).piece->getType());
	}

	return (value);
}

int		chessAi::evaluateCenter(void)
{
	int	value = 0;

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
				value = value + getMaterialValue(_board.at(i).piece->getType());
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
				value = value + getMaterialValue(_board.at(i).piece->getType());
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
		switchPlayers();
		watchers = getWatchers(kingWays.at(i));
		unSwitchPlayers();

		for (; watchers.size() != 0; watchers.pop())
			value = value + (getMaterialValue(watchers.top()->getType()) * (-1));
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
			value = value + getMaterialValue(watchers.top()->getType());
	}

	return (value);
}

int		chessAi::evaluateMobility(void)
{
	;
}

int		chessAi::getScore(void)
{
	int	score = 0;

	score = score + evaluateMaterial();
	score = score + evaluateDefense();

	score = score + evaluateKingControl();
	score = score + evaluateKingDefense();

	score = score + evaluateCenter();
	// ...

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

// – mobilité
// (nb de coups possible pour chaque pièces)

// – promotion
// (pions proches)

// – contrôle du centre
// (visée du centre = e4/e5/d4/d5)

// – sécurité du roi allié v
// (visée adverse case alentours)

// – structure de pions
// (doublés/isolés/en arrière)
// (défendus/structurés/en avant)

// – développement
// (cavaliers/fous/roque)

// – positionnement
// (occupation du centre = e4/e5/d4/d5)
