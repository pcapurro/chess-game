#include "chessAi.hpp"

chessAi::chessAi(const chessBoard *board) : chessBoard(board)
{
	_nextMove.clear();

	_simulation = false;
}
