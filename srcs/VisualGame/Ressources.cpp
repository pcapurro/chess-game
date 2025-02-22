#include "VisualGame/VisualGame.hpp"

void	VisualGame::loadTexts(void)
{
	int	value = 0;

	value += _textures->texts.blackToPlay.load(_mainRenderer, \
		"./materials/texts/black-to-play.bmp");
	value += _textures->texts.whiteToPlay.load(_mainRenderer, \
		"./materials/texts/white-to-play.bmp");

	value += _textures->texts.whiteWon.load(_mainRenderer, \
		"./materials/texts/white-won.bmp");
	value += _textures->texts.blackWon.load(_mainRenderer, \
		"./materials/texts/black-won.bmp");

	value += _textures->texts.draw.load(_mainRenderer, \
		"./materials/texts/draw.bmp");

	if (value != 0)
		throw std::runtime_error("SDL failed.");
}

void	VisualGame::loadLetters(void)
{
	int	value = 0;

	value += _textures->letters.a.load(_mainRenderer, \
		"./materials/letters/a.bmp", 'a');
	value += _textures->letters.b.load(_mainRenderer, \
		"./materials/letters/b.bmp", 'b');
	value += _textures->letters.c.load(_mainRenderer, \
		"./materials/letters/c.bmp", 'c');
	value += _textures->letters.d.load(_mainRenderer, \
		"./materials/letters/d.bmp", 'd');

	value += _textures->letters.e.load(_mainRenderer, \
		"./materials/letters/e.bmp", 'e');
	value += _textures->letters.f.load(_mainRenderer, \
		"./materials/letters/f.bmp", 'f');
	value += _textures->letters.g.load(_mainRenderer, \
		"./materials/letters/g.bmp", 'g');
	value += _textures->letters.h.load(_mainRenderer, \
		"./materials/letters/h.bmp", 'h');


	if (value != 0)
		throw std::runtime_error("SDL failed.");
}

void	VisualGame::loadNumbers(void)
{
	int	value = 0;

	value += _textures->numbers.zero.load(_mainRenderer, \
		"./materials/numbers/0.bmp", '0');
	value += _textures->numbers.one.load(_mainRenderer, \
		"./materials/numbers/1.bmp", '1');
	value += _textures->numbers.two.load(_mainRenderer, \
		"./materials/numbers/2.bmp", '2');
	value += _textures->numbers.three.load(_mainRenderer, \
		"./materials/numbers/3.bmp", '3');
	value += _textures->numbers.four.load(_mainRenderer, \
		"./materials/numbers/4.bmp", '4');

	value += _textures->numbers.five.load(_mainRenderer, \
		"./materials/numbers/5.bmp", '5');
	value += _textures->numbers.six.load(_mainRenderer, \
		"./materials/numbers/6.bmp", '6');
	value += _textures->numbers.seven.load(_mainRenderer, \
		"./materials/numbers/7.bmp", '7');
	value += _textures->numbers.eight.load(_mainRenderer, \
		"./materials/numbers/8.bmp", '8');
	value += _textures->numbers.nine.load(_mainRenderer, \
		"./materials/numbers/9.bmp", '9');

	if (value != 0)
		throw std::runtime_error("SDL failed.");
}

void	VisualGame::loadWhiteTextures(void)
{
	int	value = 0;

	value += _textures->whiteTextures.king.load(_mainRenderer, \
		"./materials/white/king.bmp", 'K');
	value += _textures->whiteTextures.queen.load(_mainRenderer, \
		"./materials/white/queen.bmp", 'Q');

	value += _textures->whiteTextures.knight.load(_mainRenderer, \
		"./materials/white/knight.bmp", 'N');
	value += _textures->whiteTextures.bishop.load(_mainRenderer, \
		"./materials/white/bishop.bmp", 'B');
	value += _textures->whiteTextures.rook.load(_mainRenderer, \
		"./materials/white/rook.bmp", 'R');

	value += _textures->whiteTextures.pawn.load(_mainRenderer, \
		"./materials/white/pawn.bmp", 'P');

	if (value != 0)
		throw std::runtime_error("SDL failed.");
}

void	VisualGame::loadBlackTextures(void)
{
	int	value = 0;

	value += _textures->blackTextures.king.load(_mainRenderer, \
		"./materials/black/king.bmp", 'K');
	value += _textures->blackTextures.queen.load(_mainRenderer, \
		"./materials/black/queen.bmp", 'Q');

	value += _textures->blackTextures.knight.load(_mainRenderer, \
		"./materials/black/knight.bmp", 'N');
	value += _textures->blackTextures.bishop.load(_mainRenderer, \
		"./materials/black/bishop.bmp", 'B');
	value += _textures->blackTextures.rook.load(_mainRenderer, \
		"./materials/black/rook.bmp", 'R');

	value += _textures->blackTextures.pawn.load(_mainRenderer, \
		"./materials/black/pawn.bmp", 'P');

	if (value != 0)
		throw std::runtime_error("SDL failed.");
}

void	VisualGame::loadBoardTextures(void)
{
	int	value = 0;

	value += _textures->boardTexture.load(_mainRenderer, \
		"./materials/board.bmp");

	value += _textures->symbols.checkMateWhite.load(_mainRenderer, \
		"./materials/symbols/checkmate-white.bmp", 'c');
	value += _textures->symbols.checkMateBlack.load(_mainRenderer, \
		"./materials/symbols/checkmate-black.bmp", 'c');

	value += _textures->promotion.load(_mainRenderer, \
		"./materials/symbols/promotion.bmp");

	value += _textures->symbols.plus.load(_mainRenderer, \
		"./materials/symbols/plus.bmp");

	if (value != 0)
		throw std::runtime_error("SDL failed.");
}

void	VisualGame::loadTextures(void)
{
	loadTexts();

	loadLetters();
	loadNumbers();

	loadBoardTextures();

	loadWhiteTextures();
	loadBlackTextures();
}
