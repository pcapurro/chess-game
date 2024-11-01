#include "../include/chessGame.hpp"
#include "chessBoard/chessBoard.hpp"

string	getStockfishAnswer(const void *boardPtr, const int turn)
{
	if (turn % 2 == 0)
		return ("e4");
	return ("e5");
}
