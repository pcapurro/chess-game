#include "chessAi.hpp"

int		chessAi::evaluateMaterial(void)
{
	int	value = 0;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() == _gameInfo._color)
			value += getMaterialValue(_board.at(i).piece->getType());
	}

	cout << "adding material value > " << value << endl;

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

	cout << "adding defense value > " << value << endl;

	return (value);
}

int		chessAi::evaluateAttack(void)
{
	int				value = 0;
	string			move, dest;
	vector<string>	legalMoves;

	legalMoves = getLegalMoves();

	for (int i = 0; i != legalMoves.size(); i++)
	{
		move = legalMoves.at(i);
		if (count(move.begin(), move.end(), 'O') == 0)
		{
			move = move.c_str() + 1;
			dest = string(1, move[2]) + move[3];

			if (_board.at(getAtValue(dest)).piece != NULL)
			{
				if (isMoveWorth(move) == true)
					value += _board.at(getAtValue(dest)).piece->getType();
			}
		}
	}

	cout << "adding attack value > " << value << endl;

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
	
	cout << "adding enemy king control value > " << value << endl;

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

	cout << "adding ally king defense value > " << value << endl;

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

	cout << "adding ally mobility value > " << value << endl;

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

	cout << "adding ally promotion value > " << value << endl;

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

	cout << "adding ally pawns dev value > " << value << endl;

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

	cout << "adding ally center control value > " << value << endl;

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

	cout << "adding ally global dev value > " << value << endl;

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

	if (_gameInfo._color == "white")
		whiteScore = getScore(), cout << "white score > " << whiteScore << endl << endl;
	else
		blackScore = getScore(), cout << "black score > " << blackScore << endl << endl;

	switchPlayers();

	if (_gameInfo._color == "white")
		whiteScore = getScore(), cout << "white score > " << whiteScore << endl << endl;
	else
		blackScore = getScore(), cout << "black score > " << blackScore << endl << endl;

	unSwitchPlayers();	
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