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
	bool	_check;
	bool	_checkmate;
	bool	_draw;

	t_move	_lastMove;
	bool	_moveFailed;

	bool	_whiteCastle;
	bool	_whiteCastled;
	string	_whiteCastleLost;

	bool	_blackCastle;
	bool	_blackCastled;
	string	_blackCastleLost;

	bool	_enPassant;
	string	_enPassantDest;

	int		_turn;
	string	_color;

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