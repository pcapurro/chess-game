#ifndef VISUALOBJECTS_HPP
# define VISUALOBJECTS_HPP

# include "../../includes/visual.hpp"
# include "./visualTexture.hpp"

typedef struct s_pieces
{
	visualTexture	king;
	visualTexture	queen;

	visualTexture	bishop;
	visualTexture	knight;
	visualTexture	rook;

	visualTexture	pawn;

}	t_pieces;

typedef struct s_texts
{
	visualTexture	whiteWon;
	visualTexture	blackWon;
	visualTexture	whiteToPlay;
	visualTexture	blackToPlay;
	visualTexture	draw;

}	t_text;

typedef struct s_letters
{
	visualTexture	a;
	visualTexture	b;
	visualTexture	c;
	visualTexture	d;

	visualTexture	e;
	visualTexture	f;
	visualTexture	g;
	visualTexture	h;

}	t_letters;

typedef struct s_numbers
{
	visualTexture	zero;
	visualTexture	one;
	visualTexture	two;
	visualTexture	three;
	visualTexture	four;

	visualTexture	five;
	visualTexture	six;
	visualTexture	seven;
	visualTexture	eight;
	visualTexture	nine;

}	t_numbers;

typedef struct s_symbols
{
	visualTexture	plus;

	visualTexture	checkMateWhite;
	visualTexture	checkMateBlack;

}	t_symbols;

typedef struct s_textures
{
	visualTexture	boardTexture;
	visualTexture	promotion;

	t_pieces		whiteTextures;
	t_pieces		blackTextures;

	t_letters		letters;
	t_numbers		numbers;

	t_symbols		symbols;

	t_text			texts;

}	t_textures;

typedef struct s_visual_infos
{
		string			_droppedSrc;
		string			_clickSrc;
		string			_droppedDest;
		vector<string>	_droppedDests;

		int				_x;
		int				_y;

		bool			_visualCoords;
		string			_actualCoords;

		string			_lastMove;

		bool			_evaluation;
		int				_whiteScore;
		int				_blackScore;

		int				_aiSide;
		int				_turn;

		int				_boardColor;
		vector<int>		_boardColors;

		bool				_code;
		vector<SDL_Keycode>	_keyHistory;

}	t_visual_infos;

#endif