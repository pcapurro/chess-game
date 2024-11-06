#include "aiChess.hpp"
#include "../chessBoard/chessBoard.hpp"

aiChess::aiChess(void) {;}

aiChess::~aiChess(void) {;}

string	aiChess::getNextMove(chessBoard *board, const int aiSide)
{
	string		aiColor;
	string		playerColor;

	chessBoard	newBoard;

	if (aiSide % 2 == 0)
		aiColor = "white", playerColor = "black";
	else
		aiColor = "black", playerColor = "white";

	newBoard = board;

	return (string(""));
}

// 0. endgame ou start/middle game ?
// 2. échec et mat dans 1 move ?
// 3. échec et mat dans 2 moves ?

// 1. = move sans perte ?
// 4. = move empêche le roque (= menace case roque + pas de perte) ?
// 5. = move protégé ?