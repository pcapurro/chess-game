#include "ChessBoard/ChessBoard.hpp"

ChessBoard::ChessBoard(void)
{
	_gameInfo.turn = 0;
	_gameInfo.color = "white";

	_gameInfo.moveFailed = false;

	_gameInfo.whiteCastle = true;
	_gameInfo.blackCastle = true;

	_gameInfo.whiteCastled = false;
	_gameInfo.blackCastled = false;
	
	_gameInfo.draw = false;
	_gameInfo.checkmate = false;

	_gameInfo.enPassant = false;
	_gameInfo.enPassantSrcOne = "";
	_gameInfo.enPassantSrcTwo = "";
	_gameInfo.enPassantDest = "";

	_boardCount.whiteMaterial = 39;
	_boardCount.blackMaterial = 39;

	initBoard();
}

void	ChessBoard::initBishops(void)
{
	_board.push_back({new Bishop("white", "c1"), "c1"});
	_board.push_back({new Bishop("white", "f1"), "f1"});
	_board.push_back({new Bishop("black", "c8"), "c8"});
	_board.push_back({new Bishop("black", "f8"), "f8"});
}

void	ChessBoard::initRooksKnights(void)
{
	_board.push_back({new Knight("white", "g1"), "g1"});
	_board.push_back({new Knight("white", "b1"), "b1"});
	_board.push_back({new Knight("black", "g8"), "g8"});
	_board.push_back({new Knight("black", "b8"), "b8"});

	_board.push_back({new Rook("white", "a1"), "a1"});
	_board.push_back({new Rook("white", "h1"), "h1"});
	_board.push_back({new Rook("black", "a8"), "a8"});
	_board.push_back({new Rook("black", "h8"), "h8"});
}

void	ChessBoard::initQueensKings(void)
{
	_board.push_back({new Queen("white", "d1"), "d1"});
	_board.push_back({new Queen("black", "d8"), "d8"});

	_board.push_back({new King("white", "e1"), "e1"});
	_board.push_back({new King("black", "e8"), "e8"});
}

void	ChessBoard::initBoard(void)
{
	for (int i = 0; i != 8; i++)
	{
		for (int k = 0; k != 8; k++)
		{
			std::string coord = "abcdefgh"[i] + std::to_string(k + 1);
			if (k + 1 == 2)
				_board.push_back({new Pawn ("white", coord), coord});
			if (k + 1 == 7)
				_board.push_back({new Pawn ("black", coord), coord});
			
			if (k + 1 >= 3 && k + 1 <= 6)
				_board.push_back({nullptr, coord});
		}
	}
	initRooksKnights();
	initBishops();
	initQueensKings();
}
