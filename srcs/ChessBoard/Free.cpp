#include "ChessBoard/ChessBoard.hpp"

ChessBoard::~ChessBoard(void)
{
	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece != nullptr)
			delete (_board.at(i).piece), _board.at(i).piece = nullptr;
	}
}
