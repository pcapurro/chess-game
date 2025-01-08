#include "ChessBoard.hpp"

ChessBoard::~ChessBoard(void)
{
	if (_free == true)
	{
		for (int i = 0; i != 64; i++)
		{
			if (_board.at(i).piece != nullptr)
				delete _board.at(i).piece, _board.at(i).piece = nullptr;
		}
		_board.clear();
	}
}

bool	ChessBoard::checkBoardAllocation(void) const
{
	for (int i = 0; i != 64; i++)
	{
		if (_board.at(i).piece == nullptr \
			&& (_board.at(i).coord[1] == '1' || _board.at(i).coord[1] == '2' \
			|| _board.at(i).coord[1] == '8' || _board.at(i).coord[1] == '7'))
			return (false);
	}

	return (true);
}
