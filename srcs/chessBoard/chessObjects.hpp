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

typedef struct s_square
{
	chessPiece	*piece;
	string		coord;

}	t_square;

typedef struct s_game_info
{
	bool	check;
	bool	checkmate;
	bool	draw;

	t_move	lastMove;
	bool	moveFailed;

	bool	whiteCastle;
	bool	whiteCastled;
	string	whiteCastleLost;

	bool	blackCastle;
	bool	blackCastled;
	string	blackCastleLost;

	bool	enPassant;
	string	enPassantDest;

	int		turn;
	string	color;

}	t_game_info;

typedef struct s_counter
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

}	t_counter;

#endif