#ifndef VISUALOBJECTS_HPP
# define VISUALOBJECTS_HPP

# include "../../includes/visual.hpp"
# include "./visualTexture.hpp"

struct Pieces
{
	visualTexture	king;
	visualTexture	queen;

	visualTexture	bishop;
	visualTexture	knight;
	visualTexture	rook;

	visualTexture	pawn;
};

struct Texts
{
	visualTexture	whiteWon;
	visualTexture	blackWon;
	visualTexture	whiteToPlay;
	visualTexture	blackToPlay;
	visualTexture	draw;
};

struct Letters
{
	visualTexture	a;
	visualTexture	b;
	visualTexture	c;
	visualTexture	d;

	visualTexture	e;
	visualTexture	f;
	visualTexture	g;
	visualTexture	h;
};

struct Numbers
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
};

struct Symbols
{
	visualTexture	plus;

	visualTexture	checkMateWhite;
	visualTexture	checkMateBlack;
};

struct Textures
{
	visualTexture	boardTexture;
	visualTexture	promotion;

	Pieces			whiteTextures;
	Pieces			blackTextures;

	Letters			letters;
	Numbers			numbers;

	Symbols			symbols;

	Texts			texts;
};

struct VisualInfos
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
};

#endif