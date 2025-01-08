#ifndef CHESSOBJECTS
# define CHESSOBJECTS

# include "../../includes/Game.hpp"

# include "pieces/ChessPiece.hpp"
# include "pieces/King.hpp"
# include "pieces/Queen.hpp"
# include "pieces/Rook.hpp"
# include "pieces/Bishop.hpp"
# include "pieces/Knight.hpp"
# include "pieces/Pawn.hpp"

struct Square
{
	ChessPiece*	piece;
	string		coord;
};

struct GameInfo
{
	bool	check;
	bool	checkmate;
	bool	draw;

	Move	lastMove;
	bool	moveFailed;

	bool	whiteCastle;
	bool	whiteCastled;
	string	whiteCastleLost;

	bool	blackCastle;
	bool	blackCastled;
	string	blackCastleLost;

	bool	enPassant;
	string	enPassantSrcOne;
	string	enPassantSrcTwo;
	string	enPassantDest;

	int		turn;
	string	color;
};

struct Counter
{
	int	whiteKing;
	int	blackKing;

	int	whiteQueen;
	int	blackQueen;

	int	whiteRook;
	int	blackRook;

	int	whiteBishop;
	int	blackBishop;

	int	whiteKnight;
	int	blackKnight;

	int	whitePawn;
	int	blackPawn;

	int	whiteMaterial;
	int	blackMaterial;

	int	total;
};

#endif