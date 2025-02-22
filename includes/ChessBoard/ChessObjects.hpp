#ifndef CHESSOBJECTS
# define CHESSOBJECTS

# include "Game.hpp"

# include "ChessBoard/ChessPiece.hpp"
# include "ChessBoard/King.hpp"
# include "ChessBoard/Queen.hpp"
# include "ChessBoard/Rook.hpp"
# include "ChessBoard/Bishop.hpp"
# include "ChessBoard/Knight.hpp"
# include "ChessBoard/Pawn.hpp"

struct Square
{
	ChessPiece*	piece;
	std::string		coord;
};

struct GameInfo
{
	bool		check;
	bool		checkmate;
	bool		draw;

	Move		lastMove;
	bool		moveFailed;

	bool		whiteCastle;
	bool		whiteCastled;
	std::string	whiteCastleLost;

	bool		blackCastle;
	bool		blackCastled;
	std::string	blackCastleLost;

	bool		enPassant;
	std::string	enPassantSrcOne;
	std::string	enPassantSrcTwo;
	std::string	enPassantDest;

	int			turn;
	std::string	color;
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