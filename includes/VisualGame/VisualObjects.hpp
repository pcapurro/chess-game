#ifndef VISUALOBJECTS_HPP
# define VISUALOBJECTS_HPP

# include "../../includes/Visual.hpp"
# include "./VisualTexture.hpp"

struct Pieces
{
	VisualTexture	king;
	VisualTexture	queen;

	VisualTexture	bishop;
	VisualTexture	knight;
	VisualTexture	rook;

	VisualTexture	pawn;
};

struct Texts
{
	VisualTexture	whiteWon;
	VisualTexture	blackWon;
	VisualTexture	whiteToPlay;
	VisualTexture	blackToPlay;
	VisualTexture	draw;
};

struct Letters
{
	VisualTexture	a;
	VisualTexture	b;
	VisualTexture	c;
	VisualTexture	d;

	VisualTexture	e;
	VisualTexture	f;
	VisualTexture	g;
	VisualTexture	h;
};

struct Numbers
{
	VisualTexture	zero;
	VisualTexture	one;
	VisualTexture	two;
	VisualTexture	three;
	VisualTexture	four;

	VisualTexture	five;
	VisualTexture	six;
	VisualTexture	seven;
	VisualTexture	eight;
	VisualTexture	nine;
};

struct Symbols
{
	VisualTexture	plus;

	VisualTexture	checkMateWhite;
	VisualTexture	checkMateBlack;
};

struct Textures
{
	VisualTexture	boardTexture;
	VisualTexture	promotion;

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