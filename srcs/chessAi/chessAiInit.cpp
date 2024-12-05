#include "chessAi.hpp"

chessAi::chessAi(const chessBoard *board) : chessBoard(board)
{
	_nextMove.clear();

	_checkMateInOne = false;
	_checkMateInTwo = false;
	_defeatNext = false;
	_allyAttacked = false;
	_allyLost = false;
	_allyAttackedNext = false;
	_check = false;
}
