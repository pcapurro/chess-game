#ifndef CHESSOBJECTS
# define CHESSOBJECTS

# include "../../includes/game.hpp"

# include "pieces/chessPiece.hpp"
# include "pieces/king.hpp"
# include "pieces/queen.hpp"
# include "pieces/rook.hpp"
# include "pieces/bishop.hpp"
# include "pieces/knight.hpp"
# include "pieces/pawn.hpp"

struct Square
{
	chessPiece	*piece;
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