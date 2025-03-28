#include "ChessBoard/ChessBoard.hpp"

bool	ChessBoard::isCheck(void)
{
	std::string					kingPos;
	std::string					kingColor;
	std::vector<std::string>	boardCoords;

	boardCoords = getPiecesCoords();
	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != nullptr && _board.at(i).piece->getType() == 'K' \
			&& _board.at(i).piece->getColor() == _gameInfo.color)
			kingPos = _board.at(i).coord, kingColor = _board.at(i).piece->getColor();
	}
	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != nullptr && _board.at(i).piece->getColor() != kingColor)
		{
			if (_board.at(i).piece->isOnMyWay(kingPos, boardCoords, 1) == true)
				return (true);
		}
	}

	return (false);
}

bool	ChessBoard::canAnyAllyPieceMove(void)
{
	std::vector<std::string>	boardCoords;

	boardCoords = getPiecesCoords();
	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != nullptr && _board.at(i).piece->getColor() == _gameInfo.color \
			&& _board.at(i).piece->getType() != 'K')
		{
			for (int k = 0; k != 64; k++)
			{
				if (_board.at(i).piece->isOnMyWay(_board.at(k).coord, boardCoords, 0, _gameInfo.enPassantDest) == true \
					&& doesItResolveCheck(_board.at(i).coord + _board.at(k).coord) == true)
					return (true);
			}
		}
	}

	return (false);
}

bool	ChessBoard::isCheckMateImpossible(void)
{
	countPiecesOnBoard();

	if (_boardCount.total == 2)
		return (true);

	if (_boardCount.whiteKing + _boardCount.blackKing \
		+ _boardCount.whiteKnight + _boardCount.blackKnight \
		== 6 && 6 == _boardCount.total)
		return (true);

	if (_boardCount.whiteKing + _boardCount.blackKing \
		+ _boardCount.whiteKnight + _boardCount.blackKnight \
		== 4 && 4 == _boardCount.total)
		return (true);

	if (_boardCount.whiteKing + _boardCount.blackKing \
		+ _boardCount.whiteKnight + _boardCount.blackKnight \
		== 3 && 3 == _boardCount.total)
		return (true);

	if (_boardCount.whiteKing + _boardCount.blackKing \
		+ _boardCount.whiteBishop + _boardCount.blackBishop \
		== 4 && 4 == _boardCount.total)
		return (true);

	if (_boardCount.whiteKing + _boardCount.blackKing \
		+ _boardCount.whiteBishop + _boardCount.blackBishop \
		== 3 && 3 == _boardCount.total)
		return (true);

	if (_boardCount.whitePawn + _boardCount.blackPawn \
		+ _boardCount.whiteKing + _boardCount.blackKing \
		== _boardCount.total)
	{
		if (canTheKingMove() == false && canAnyAllyPieceMove() == false)
			return (true);
	}

	return (false);
}

bool	ChessBoard::canTheKingMove(void)
{
	int							kingPos;
	std::string					kingColor;
	std::vector<std::string>	boardCoords;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != nullptr && _board.at(i).piece->getType() == 'K' \
			&& _board.at(i).piece->getColor() == _gameInfo.color)
			kingPos = i, kingColor = _board.at(i).piece->getColor();
	}
	for (int i = 0; i != 64; i++)
	{
		if (_board.at(kingPos).piece->isOnMyWay(_board.at(i).coord, boardCoords) == true)
		{
			boardCoords = getPiecesCoords();
			if ((_board.at(i).piece == nullptr || _board.at(i).piece->getColor() != kingColor) \
				&& doesItResolveCheck(_board.at(kingPos).coord + _board.at(i).coord) == true)
				return (true);
		}
	}

	return (false);
}

bool	ChessBoard::isDraw(void)
{
	if (isCheck() == false)
	{
		if (isCheckMateImpossible() == true \
			|| (canTheKingMove() == false && canAnyAllyPieceMove() == false))
			{ _gameInfo.draw = true; return (true); }
	}

	return (false);
}

bool	ChessBoard::doesItResolveCheck(const std::string& srcdest)
{
	tryMove(srcdest);

	if (isCheck() == true)
		{ undoMove(srcdest); return (false); }
	undoMove(srcdest);

	return (true);
}

std::vector<std::string>	ChessBoard::getPossibleTargets(const std::string& coord) const
{
	int							atValue;
	std::string					coords;
	std::vector<std::string>	boardCoords;
	std::vector<std::string>	moves;

	atValue = getAtValue(coord);
	boardCoords = getPiecesCoords();

	for (int i = 0; i != 8; i++)
	{
		for (int k = 0; k != 8; k++)
		{
			coords = "abcdefgh"[i] + std::to_string(k + 1);
			if (_board.at(atValue).piece->isOnMyWay(coords, boardCoords, 0, _gameInfo.enPassantDest) == true)
			{
				if (_board.at(getAtValue(coords)).piece == nullptr \
					|| _board.at(getAtValue(coords)).piece->getColor() != _gameInfo.color)
					moves.push_back(coord + coords);
			}
		}
	}

	return (moves);
}

bool	ChessBoard::isCheckMate(const int value)
{
	if (isCheck() == true)
	{
		if (value == 0)
			_gameInfo.check = true;

		std::vector<std::string>	sources;

		for (int i = 0; i != 64; i++)
		{
			if (_board.at(i).piece != nullptr && _board.at(i).piece->getColor() == _gameInfo.color)
			{
				sources = getPossibleTargets(_board.at(i).coord);
				for (size_t k = 0; k != sources.size(); k++)
				{
					if (doesItResolveCheck(sources.at(k)) == true)
						return (false);
				}
			}
			sources.clear();
		}
		if (value == 0)
			_gameInfo.checkmate = true;

		return (true);
	}
	else if (value == 0)
		_gameInfo.check = false;

	return (false);
}

bool	ChessBoard::isGameOver(void)
{
	if (isCheckMate() == true)
		return (true);
	if (isDraw() == true)
		return (true);

	return (false);
}
