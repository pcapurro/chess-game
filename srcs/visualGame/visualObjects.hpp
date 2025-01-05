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
		string			droppedSrc;
		string			clickSrc;

		string			droppedDest;
		vector<string>	droppedDests;
		bool			visualDests;

		int				x;
		int				y;

		bool			promotion;

		bool			visualCoords;
		string			actualCoords;

		string			lastMove;

		bool			evaluation;
		int				whiteScore;
		int				blackScore;

		int				aiSide;
		int				turn;

		int				boardColor;
		vector<int>		boardColors;

		bool				code;
		vector<SDL_Keycode>	keyHistory;

}	t_visual_infos;

#endif