#include "../chessBoard.hpp"

size_t	chessBoard::getAtValue(const string coord) const
{
	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).coord[0] == coord[0]
			&& _board.at(i).coord[1] == coord[1])
			return (i);
	}

	return (0);
}

vector<string>	chessBoard::getPiecesCoords(void) const
{
	vector<string>	coords;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != nullptr && _board.at(i).piece->isVisible() == true)
			coords.push_back(_board.at(i).coord);
	}

	return (coords);
}

vector<string>	chessBoard::getLegalMoves(void)
{
	char			type;
	string			move;
	vector<string>	possibleMoves;
	vector<string>	legalMoves;
	vector<string>	availaibleTargets;

	possibleMoves.push_back("O-O");
	possibleMoves.push_back("O-O-O");

	for (int i = 0; i != 8; i++)
	{
		for (int k = 0; k != 8; k++)
		{
			string coord = "abcdefgh"[i] + to_string(k + 1);
			if (_board.at(getAtValue(coord)).piece != nullptr 
				&& _board.at(getAtValue(coord)).piece->getColor() == _gameInfo._color)
			{
				availaibleTargets = getPossibleTargets(coord);
				for (size_t j = 0; j != availaibleTargets.size(); j++)
				{
					type = _board.at(getAtValue(coord)).piece->getType();
					move = string{type} + availaibleTargets.at(j);
					
					if ((move.at(move.length() - 1) == '8' || move.at(move.length() - 1) == '1') && type == 'P')
						possibleMoves.push_back(move + 'Q'), possibleMoves.push_back(move + 'B'), \
						possibleMoves.push_back(move + 'N'), possibleMoves.push_back(move + 'R');
					else
						possibleMoves.push_back(move);
				}
				availaibleTargets.clear();
			}
		}
	}

	for (size_t i = 0; i != possibleMoves.size(); i++)
	{
		if (isLegal(possibleMoves.at(i)) == true)
			legalMoves.push_back(possibleMoves.at(i));
	}

	return (legalMoves);
}

vector<string>	chessBoard::getCastlingSrcsDests(const string srcdest) const
{
	char			y;
	string			src;
	string			dest;
	vector<string>	srcsDests;

	_gameInfo._color == "white" ? y = '1' : y = '8';

	if (srcdest == "O-O")
	{
		src = {'e', y}, dest = {'g', y};
		srcsDests.push_back(src + dest);

		src = {'h', y}, dest = {'f', y};
		srcsDests.push_back(src + dest);
	}
	if (srcdest == "O-O-O")
	{
		src = {'e', y}, dest = {'c', y};
		srcsDests.push_back(src + dest);

		src = {'a', y}, dest = {'d', y};
		srcsDests.push_back(src + dest);
	}

	return (srcsDests);
}

int	chessBoard::getStateValue(void) const
{
	if (_gameInfo._checkmate == true)
		return (1);
	if (_gameInfo._draw == true || isAllocated() == false)
		return (2);

	return (0);
}

string	chessBoard::getEnPassantTarget(void) const
{
	string	target;

	target = _gameInfo._enPassantDest;
	if (_gameInfo._turn % 2 == 0)
		target[1] = target[1] + 1;
	if (_gameInfo._turn % 2 == 1)
		target[1] = target[1] - 1;
	
	return (target);
}

int	chessBoard::getWatchersNumber(const string coord) const
{
	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != nullptr)
		{
			if (_board.at(i).piece->getColor() == _gameInfo._color && _board.at(i).coord != coord
				&& _board.at(i).piece->isVisible() == true)
			{
				if (_board.at(i).piece->isOnMyWay(coord, getPiecesCoords(), 1, _gameInfo._enPassantDest) == true)
					return (1);
			}
		}
	}

	return (0);
}

stack<cP *>	chessBoard::getWatchers(const string coord)
{
	vector<string>		baordCoords;
	stack<cP *>			material;
	stack<cP *>			material3;
	vector<stack<cP *>>	materials;

	while (getWatchersNumber(coord) != 0)
	{
		baordCoords = getPiecesCoords();

		for (int i = 0; i != 64; i++)
		{
			if (_board.at(i).piece != nullptr)
			{
				if (_board.at(i).piece->getColor() == _gameInfo._color && _board.at(i).coord != coord
					&& _board.at(i).piece->isVisible() == true)
				{
					if (_board.at(i).piece->isOnMyWay(coord, baordCoords, 1, _gameInfo._enPassantDest) == true)
					{
						material.push(_board.at(i).piece);
						_board.at(i).piece->setVisibility();
					}
				}
			}
		}
		material = orderByValue(material);
		materials.push_back(material);
		while (material.size() != 0)
			material.pop();
	}

	if (materials.size() != 0)
	{
		for (int i = materials.size() - 1; i != -1; i--)
		{
			while (materials.at(i).size() != 0)
			{
				material3.push(materials.at(i).top());
				material3.top()->setVisibility();
				materials.at(i).pop();
			}
		}
	}

	return (material3);
}

int	chessBoard::getMaterialValue(const char type) const
{
	if (type == 'P')
		return (1);
	if (type == 'N' || type == 'B')
		return (3);
	if (type == 'R')
		return (5);
	if (type == 'Q')
		return (9);
	if (type == 'K')
		return (200);

	return (0);
}

char	chessBoard::getType(const string coord) const
{
	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).coord == coord && _board.at(i).piece != nullptr)
			return (_board.at(i).piece->getType());
	}

	return (' ');
}

string	chessBoard::getColor(const string coord) const
{
	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).coord == coord && _board.at(i).piece != nullptr)
			return (_board.at(i).piece->getColor());
	}

	return ("");
}

stack<chessPiece *>	chessBoard::orderByValue(stack<chessPiece *> materials) const
{
	stack<cP *>		stack;
	vector<cP *>	vMaterials;

	while (materials.size() != 0)
		vMaterials.push_back(materials.top()), materials.pop();

	for (int i = 0; i != 5; i++)
	{
		for (size_t k = 0; k != vMaterials.size(); k++)
		{
			if (i == 4 && vMaterials.at(k)->getType() == 'K')
				stack.push(vMaterials.at(k));
			if (i == 3 && vMaterials.at(k)->getType() == 'Q')
				stack.push(vMaterials.at(k));
			if (i == 2 && vMaterials.at(k)->getType() == 'R')
				stack.push(vMaterials.at(k));
			if (i == 1 && (vMaterials.at(k)->getType() == 'B' || vMaterials.at(k)->getType() == 'N'))
				stack.push(vMaterials.at(k));
			if (i == 0 && vMaterials.at(k)->getType() == 'P')
				stack.push(vMaterials.at(k));
		}
	}

	return (stack);
}
