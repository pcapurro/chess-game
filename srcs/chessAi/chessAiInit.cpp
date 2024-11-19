#include "chessAi.hpp"

chessAi::chessAi(const chessBoard *board) : chessBoard(board)
{
	_nextMove.clear();
	_attackedAlly.clear();

	_victoryNextNext = false;
	_defeatNext = false;
	_allyAttacked = false;
	_check = false;
}
