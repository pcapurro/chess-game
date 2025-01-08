#include "../chessBoard.hpp"

int	chessBoard::checkPawnDest(void) const
{
	string	src = _gameInfo.lastMove.src;
	string	dest = _gameInfo.lastMove.dest;
	int		atValue = getAtValue(dest);

	if ((_board.at(atValue).coord[1] == '8' || _board.at(atValue).coord[1] == '1') \
		&& (dest.length() != 3 || algebraParser::isChessPiece(dest[2]) == false \
		|| dest[2] == 'K'))
		return (1);

	if (_board.at(atValue).coord[0] != src[0])
	{
		if (_board.at(atValue).coord[0] - 1 != src[0] \
			&& _board.at(atValue).coord[0] + 1 != src[0])
			return (1);

		if (_board.at(atValue).piece == nullptr)
		{
			if ((_gameInfo.enPassant == false || _gameInfo.enPassantDest != dest))
				return (1);
		}
		else
		{
			if (_gameInfo.color == "white" && src[1] != dest[1] - 1)
				return (1);
			if (_gameInfo.color == "black" && src[1] != dest[1] + 1)
				return (1);
		}
	}

	if (_board.at(atValue).coord[0] == src[0])
	{
		if (isThereSomething(dest) == true)
			return (1);

		if (_gameInfo.color == "white" \
			&& dest[1] - src[1] != 2 \
			&& dest[1] - src[1] != 1)
			return (1);

		if (_gameInfo.color == "black" \
			&& src[1] - dest[1] != 2 \
			&& src[1] - dest[1] != 1)
			return (1);

		if (_gameInfo.color == "white" \
			&& dest[1] - src[1] == 2 \
			&& src[1] != '2')
			return (1);

		if (_gameInfo.color == "black" \
			&& src[1] - dest[1] == 2 \
			&& src[1] != '7')
			return (1);

		string	newDest = dest;
		if (_board.at(atValue).coord[1] == dest[1] + 2)
		{
			newDest[1] = newDest[1] + 1;
			if (isThereSomething(newDest) == true)
				return (1);
		}
		if (_board.at(atValue).coord[1] == dest[1] - 2)
		{
			newDest[1] = newDest[1] - 1;
			if (isThereSomething(newDest) == true)
				return (1);
		}
	}

	return (0);
}

int	chessBoard::checkPawnSource(void)
{
	string	source;
	string*	src = &_gameInfo.lastMove.src;
	string*	dest = &_gameInfo.lastMove.dest;

	int atValue = getAtValue(*dest);
	if (_board.at(atValue).piece != nullptr)
		return (1);
	for (size_t i = 0; i != src->length(); i++)
	{
		source += src->at(i);
		if (source.length() == 2)
		{
			if (_board.at(getAtValue(source)).piece != nullptr
				&& _board.at(getAtValue(source)).piece->getType() == 'P')
			{
				if (source[1] == (*dest)[1] - 2 \
					&& _board.at(getAtValue(source)).piece->getMoves() != 0)
					return (1);
				if (source[1] == (*dest)[1] + 2 \
					&& _board.at(getAtValue(source)).piece->getMoves() != 0)
					return (1);
				*src = source;
				return (0);
			}
			else
				source.clear();
		}
	}
	return (1);
}

int	chessBoard::checkNormalSource(void)
{
	string*			src = &_gameInfo.lastMove.src;
	string*			dest = &_gameInfo.lastMove.dest;
	string 			source = *src;
	vector<string>	boardCoords = getPiecesCoords();

	src->clear();
	for (int i = 0; i != 64; i++)
	{
		if (source.find(_board.at(i).coord) != string::npos && _board.at(i).piece != nullptr)
		{
			if (_board.at(i).piece->getColor() == _gameInfo.color \
				&& _board.at(i).piece->getType() == _gameInfo.lastMove.obj)
			{
				if (_board.at(i).piece->isOnMyWay(*dest, boardCoords) == true)
					*src += _board.at(i).coord;
			}
		}
	}

	if (src->length() != 2)
		return (1);

	return (0);
}

int	chessBoard::checkNormalDest(void) const
{
	char			obj = _gameInfo.lastMove.obj;
	string			src = _gameInfo.lastMove.src;
	string			dest = _gameInfo.lastMove.dest;
	vector<string>	boardCoords = getPiecesCoords();

	if (obj == 'Q')
	{
		Queen	queen("white", src);
		if (queen.isOnMyWay(dest, boardCoords) == false)
			return (1);
	}
	if (obj == 'K')
	{
		King	king("white", src);
		if (king.isOnMyWay(dest, boardCoords) == false)
			return (1);
	}
	if (obj == 'B')
	{
		Bishop	bishop("white", src);
		if (bishop.isOnMyWay(dest, boardCoords) == false)
			return (1);
	}
	if (obj == 'N')
	{
		Knight	knight("white", src);
		if (knight.isOnMyWay(dest, boardCoords) == false)
			return (1);
	}
	if (obj == 'R')
	{
		Rook	rook("white", src);
		if (rook.isOnMyWay(dest, boardCoords) == false)
			return (1);
	}

	return (0);
}

bool	chessBoard::isThereValidSource(void)
{
	if (_gameInfo.lastMove.obj == 'P')
	{
		if (checkPawnSource() == 1)
			return (false);
	}
	else if (checkNormalSource() == 1)
		return (false);

	return (true);
}

bool	chessBoard::isValidEnPassant(void) const
{
	if (_gameInfo.lastMove.obj != 'P' || _gameInfo.enPassant == false \
		|| _gameInfo.enPassantDest != _gameInfo.lastMove.dest)
		return (false);

	if (_gameInfo.lastMove.src != _gameInfo.enPassantSrcOne \
		&& _gameInfo.lastMove.src != _gameInfo.enPassantSrcTwo)
		return (false);

	string	dest;
	string	color, otherColor;

	dest = _gameInfo.enPassantDest;
	dest[1] = _gameInfo.lastMove.src[1];
	
	color = _board.at(getAtValue(_gameInfo.lastMove.src)).piece->getColor();
	otherColor = _board.at(getAtValue(dest)).piece->getColor();

	if (color == otherColor)
		return (false);

	return (true);
}

bool    chessBoard::isItValidSource(void) const
{
	int	atValue = getAtValue(_gameInfo.lastMove.src);

	if (_board.at(atValue).piece == nullptr \
		|| _board.at(atValue).piece->getType() != _gameInfo.lastMove.obj)
		return (false);

	return (true);
}

bool    chessBoard::isLegal(const string move)
{
	char*	obj;
	string*	src;
	string*	dest;

	if (move != "")
		loadMove(move);

	obj = &_gameInfo.lastMove.obj;
	src = &_gameInfo.lastMove.src;
	dest = &_gameInfo.lastMove.dest;

	if (*dest == "O-O-O" || *dest == "O-O")
	{
		if (isCastlingPossible(*dest) == false || isCheck() == true)
			return (false);
	}
	else
	{
		if (_gameInfo.lastMove.action == 'x' && isThereSomething(*dest) == false)
		{
			if (isValidEnPassant() == false)
				return (false);
		}

		if (src->length() != 2)
		{
			if (isThereValidSource() == false)
				return (false);
		}
		else if (isItValidSource() == false)
			return (false);

		if (*obj == 'P')
		{
			if (checkPawnDest() == 1)
				return (false);
		}
		else
			if (checkNormalDest() == 1)
				return (false);

		if (isThereAlly() == true || isRightSide() == false \
			|| (*obj == 'K' && isTheDestinationSafe() == false))
			return (false);

		if (isCheck() == false && doesItResolveCheck(*src + *dest) == false)
			return (false);

		if (isCheck() == true \
			&& doesItResolveCheck(*src + *dest) == false)
			return (false);
	}

	return (true);
}
