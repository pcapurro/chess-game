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

int		chessAi::getScore(void)
{
	int	score = 0;

	score = score + evaluateMaterial();
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

// – protection
// (nb de pièces protégées)

// – attaques
// (nb d'attaques possible)

// – contrôle du roi adverse
// (visée alliée case alentours)

// – mobilité
// (nb de coups possible pour chaque pièces)

// – promotion
// (pions proches)

// – contrôle du centre
// (visée du centre = e4/e5/d4/d5)

// – sécurité du roi allié
// (visée adverse case alentours)

// – structure de pions
// (doublés/isolés/en arrière)
// (défendus/structurés/en avant)

// – développement
// (cavaliers/fous/roque)

// – positionnement
// (occupation du centre = e4/e5/d4/d5)
