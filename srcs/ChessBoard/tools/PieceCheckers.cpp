#include "ChessBoard/ChessBoard.hpp"

bool	ChessBoard::isCastlingPossible(const string& castle)
{
	int	atValue;

	if (_gameInfo.color == "white")
	{
		if (_gameInfo.whiteCastle == false)
			return (false);

		if (castle == "O-O")
		{
			atValue = getAtValue("h1");
			if (_board.at(atValue).piece == nullptr \
				|| _board.at(atValue).piece->getMoves() != 0)
				return (false);
			
			atValue = getAtValue("g1");
			if (_board.at(atValue).piece != nullptr)
				return (false);
			atValue = getAtValue("f1");
			if (_board.at(atValue).piece != nullptr)
				return (false);

			atValue = getAtValue("e1");
			if (_board.at(atValue).piece == nullptr)
				return (false);

			if (doesItResolveCheck("e1g1") == false \
				|| doesItResolveCheck("e1f1") == false)
				return (false);
		}
		if (castle == "O-O-O")
		{
			atValue = getAtValue("a1");
			if (_board.at(atValue).piece == nullptr \
				|| _board.at(atValue).piece->getMoves() != 0)
				return (false);
			
			atValue = getAtValue("d1");
			if (_board.at(atValue).piece != nullptr)
				return (false);
			atValue = getAtValue("b1");
			if (_board.at(atValue).piece != nullptr)
				return (false);
			atValue = getAtValue("c1");
			if (_board.at(atValue).piece != nullptr)
				return (false);

			atValue = getAtValue("e1");
			if (_board.at(atValue).piece == nullptr)
				return (false);

			if (doesItResolveCheck("e1d1") == false \
				|| doesItResolveCheck("e1c1") == false)
				return (false);
		}
	}
	if (_gameInfo.color == "black")
	{
		if (_gameInfo.blackCastle == false)
			return (false);

		if (castle == "O-O")
		{
			atValue = getAtValue("h8");
			if (_board.at(atValue).piece == nullptr \
				|| _board.at(atValue).piece->getMoves() != 0)
				return (false);
			
			atValue = getAtValue("g8");
			if (_board.at(atValue).piece != nullptr)
				return (false);
			atValue = getAtValue("f8");
			if (_board.at(atValue).piece != nullptr)
				return (false);

			atValue = getAtValue("e8");
			if (_board.at(atValue).piece == nullptr)
				return (false);

			if (doesItResolveCheck("e8f8") == false \
				|| doesItResolveCheck("e8g8") == false)
				return (false);
		}
		if (castle == "O-O-O")
		{
			atValue = getAtValue("a8");
			if (_board.at(atValue).piece == nullptr \
				|| _board.at(atValue).piece->getMoves() != 0)
				return (false);

			atValue = getAtValue("d8");
			if (_board.at(atValue).piece != nullptr)
				return (false);
			atValue = getAtValue("b8");
			if (_board.at(atValue).piece != nullptr)
				return (false);
			atValue = getAtValue("c8");
			if (_board.at(atValue).piece != nullptr)
				return (false);

			atValue = getAtValue("e8");
			if (_board.at(atValue).piece == nullptr)
				return (false);

			if (doesItResolveCheck("e8d8") == false \
				|| doesItResolveCheck("e8c8") == false)
				return (false);
		}
	}

	return (true);
}

bool	ChessBoard::isTheDestinationSafe(void) const
{
	vector<string>	coords = getPiecesCoords();

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != nullptr && _board.at(i).piece->getColor() != _gameInfo.color)
		{
			if (_board.at(i).piece->isOnMyWay(_gameInfo.lastMove.dest, coords, 1, _gameInfo.enPassantDest) == true)
				return (false);
		}
	}

	return (true);
}

bool	ChessBoard::isRightSide(void) const
{
	int	atValue = getAtValue(_gameInfo.lastMove.src);

	if (_board.at(atValue).piece == nullptr \
		|| _board.at(atValue).piece->getColor() == _gameInfo.color)
		return (true);
	return (false);
}

bool	ChessBoard::isThereSomething(const string& dest) const
{
	int	atValue = getAtValue(dest);

	if (_board.at(atValue).piece != nullptr)
		return (true);
	return (false);
}

bool	ChessBoard::isThereAlly(void) const
{
	int	atValue = getAtValue(_gameInfo.lastMove.dest);

	if (_board.at(atValue).piece != nullptr \
		&& _board.at(atValue).piece->getColor() == _gameInfo.color)
		return (true);
	return (false);
}
