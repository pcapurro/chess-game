#include "../ChessBoard.hpp"

void	ChessBoard::resetCount(void)
{
	_boardCount.whiteKing = 0;
	_boardCount.blackKing = 0;

	_boardCount.whiteQueen = 0;
	_boardCount.blackQueen = 0;

	_boardCount.whiteRook = 0;
	_boardCount.blackRook = 0;

	_boardCount.whiteBishop = 0;
	_boardCount.blackBishop = 0;

	_boardCount.whiteKnight = 0;
	_boardCount.blackKnight = 0;

	_boardCount.whitePawn = 0;
	_boardCount.blackPawn = 0;

	_boardCount.total = 0;
}

void	ChessBoard::countTotalMaterials(void)
{
	_boardCount.whiteMaterial = 0;
	_boardCount.blackMaterial = 0;

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != nullptr && _board.at(i).piece->getType() != 'K')
		{
			if (_board.at(i).piece->getColor() == "white")
				_boardCount.whiteMaterial += getMaterialValue(_board.at(i).piece->getType());
			if (_board.at(i).piece->getColor() == "black")
				_boardCount.blackMaterial += getMaterialValue(_board.at(i).piece->getType());
		}
	}
}

void	ChessBoard::countPiecesOnBoard(void)
{
	resetCount();

	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != nullptr)
		{
			if (_board.at(i).piece->getType() == 'K' \
				&& _board.at(i).piece->getColor() == "white")
				_boardCount.whiteKing++;
			if (_board.at(i).piece->getType() == 'K' \
				&& _board.at(i).piece->getColor() == "black")
				_boardCount.whiteKing++;

			if (_board.at(i).piece->getType() == 'Q' \
				&& _board.at(i).piece->getColor() == "white")
				_boardCount.whiteQueen++;
			if (_board.at(i).piece->getType() == 'Q' \
				&& _board.at(i).piece->getColor() == "black")
				_boardCount.blackQueen++;

			if (_board.at(i).piece->getType() == 'N' \
				&& _board.at(i).piece->getColor() == "white")
				_boardCount.whiteKnight++;
			if (_board.at(i).piece->getType() == 'N' \
				&& _board.at(i).piece->getColor() == "black")
				_boardCount.blackKnight++;

			if (_board.at(i).piece->getType() == 'R' \
				&& _board.at(i).piece->getColor() == "white")
				_boardCount.whiteRook++;
			if (_board.at(i).piece->getType() == 'R' \
				&& _board.at(i).piece->getColor() == "black")
				_boardCount.blackRook++;

			if (_board.at(i).piece->getType() == 'B' \
				&& _board.at(i).piece->getColor() == "white")
				_boardCount.whiteBishop++;
			if (_board.at(i).piece->getType() == 'B' \
				&& _board.at(i).piece->getColor() == "black")
				_boardCount.blackBishop++;

			if (_board.at(i).piece->getType() == 'P' \
				&& _board.at(i).piece->getColor() == "white")
				_boardCount.whitePawn++;
			if (_board.at(i).piece->getType() == 'P' \
				&& _board.at(i).piece->getColor() == "black")
				_boardCount.blackPawn++;
			
			_boardCount.total++;
		}
	}
}
