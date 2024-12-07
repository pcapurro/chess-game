#include "chessAi.hpp"

chessAi::chessAi(const chessBoard *board) : chessBoard(board)
{
	_nextMove.clear();

	_endGame = false;

	_checkMateInOne = false;
	_checkMateInTwo = false;
	_defeatNext = false;
	_allyAttacked = false;
	_checkNext = false;
	_check = false;
}
