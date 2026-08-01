#ifndef CHESSOBJECTS
# define CHESSOBJECTS

# include "Game.hpp"

# include "ChessPiece.hpp"
# include "King.hpp"
# include "Queen.hpp"
# include "Rook.hpp"
# include "Bishop.hpp"
# include "Knight.hpp"
# include "Pawn.hpp"

struct Square
{
	ChessPiece*		piece;
	string			coord;
};

struct GameInfo
{
	bool			check;
	bool			checkmate;
	bool			draw;

	Move			lastMove;
	bool			moveFailed;

	bool			whiteCastle;
	bool			whiteCastled;
	string			whiteCastleLost;

	bool			blackCastle;
	bool			blackCastled;
	string			blackCastleLost;

	bool			enPassant;
	string			enPassantSrcOne;
	string			enPassantSrcTwo;
	string			enPassantDest;

	int				turn;
	string			color;
};

struct Counter
{
	int				whiteKing;
	int				blackKing;

	int				whiteQueen;
	int				blackQueen;

	int				whiteRook;
	int				blackRook;

	int				whiteBishop;
	int				blackBishop;

	int				whiteKnight;
	int				blackKnight;

	int				whitePawn;
	int				blackPawn;

	int				whiteMaterial;
	int				blackMaterial;

	int				total;
};

#endif
