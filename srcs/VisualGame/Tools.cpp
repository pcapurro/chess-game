#include "VisualGame/VisualGame.hpp"

SDL_Texture*	VisualGame::getTexture(const char type, const std::string& color) const
{
	const VisualTexture*	whiteTextures[7] = {&_textures.symbols.checkMateBlack, &_textures.whiteTextures.king, \
		&_textures.whiteTextures.queen, &_textures.whiteTextures.rook, &_textures.whiteTextures.bishop, \
		&_textures.whiteTextures.knight, &_textures.whiteTextures.pawn};

	const VisualTexture*	blackTextures[7] = {&_textures.symbols.checkMateWhite, &_textures.blackTextures.king, \
		&_textures.blackTextures.queen, &_textures.blackTextures.rook, &_textures.blackTextures.bishop, \
		&_textures.blackTextures.knight, &_textures.blackTextures.pawn};

	if (color == "white")
	{
		for (int i = 0; i != 7; i++)
		{
			if (type == whiteTextures[i]->getId())
				return (whiteTextures[i]->getTexture());
		}
	}

	if (color == "black")
	{
		for (int i = 0; i != 7; i++)
		{
			if (type == blackTextures[i]->getId())
				return (blackTextures[i]->getTexture());
		}
	}

	return (nullptr);
}

SDL_Rect	VisualGame::getRectangle(const std::string& coords, const std::string& type) const
{
	SDL_Rect	obj;

	if (type == "default")
	{
		obj.h = _height, obj.w = _width;
		obj.x = 0, obj.y = 0;
		return (obj);
	}

	if (type == "wscore" || type == "bscore")
	{
		obj.w = 14, obj.h = 35;
		obj.x = 760;

		if (type == "wscore")
			_visualInfo.aiSide % 2 == 0 ? obj.y = 72 : obj.y = 692;
		if (type == "bscore")
			_visualInfo.aiSide % 2 == 0 ? obj.y = 692 : obj.y = 72;

		return (obj);
	}

	int	x = coords[0] - 97;
	int	y = atoi(coords.c_str() + 1) - 1;

	_visualInfo.aiSide != 0 ? y = 8 - (y + 1) : x = 7 - x;

	obj.x = 105 + (80 * x), obj.y = 80 + (80 * y);

	if (type == "coordsl" || type == "coordsn")
	{
		obj.w = 14, obj.h = 35;

		if (type == "coordsl")
		{
			obj.x = obj.x + 40 - 7;
			obj.y = _height - 75;
		}
		else
			obj.x = 75, obj.y = obj.y + 40 - (obj.h / 2);
		return (obj);
	}

	if (type == "promotion")
		obj.x = obj.x - 17, obj.h = 100, obj.w = 114;
	else
		obj.h = 80, obj.w = 80;

	return (obj);
}

std::vector<char>	VisualGame::getOrderedCaptured(const std::vector<char> &captured) const
{
	std::vector<char>	newCaptured;

	for (size_t i = 0; i != captured.size(); i++)
	{
		if (find(newCaptured.begin(), newCaptured.end(), captured.at(i)) == newCaptured.end())
		{
			int value = count(captured.begin(), captured.end(), captured.at(i));
			while (value != 0)
				newCaptured.push_back(captured.at(i)), value--;
		}
	}

	return (newCaptured);
}

std::string	VisualGame::getCoord(const int x, const int y) const
{
	int	xZone;
	int	yZone;

	if (x >= 105 && x <= 745 && y >= 80 && y <= 720)
	{
		for (int i = 0; i != 8; i++)
		{
			_visualInfo.aiSide == 0 ? yZone = 80 * (i + 1) : yZone = 80 * (8 - i);

			for (int k = 0; k != 8; k++)
			{
				_visualInfo.aiSide == 0 ? xZone = 80 * (8 - k) : xZone = 80 * (k + 1);

				if (x >= xZone && x <= xZone + 105 && y >= yZone && y <= yZone + 80)
					return (std::string{ "abcdefgh"[k], "12345678"[i] });
			}
		}
	}

	return ("none");
}

std::string	VisualGame::getInput(const std::string& coord)
{
	std::string	input;

	if (coord == "end" || coord == "none" || coord == "error")
		return (coord);

	input += _board->getType(_visualInfo.droppedSrc);
	input += _visualInfo.droppedSrc + coord;

	if (input[0] == 'K')
	{
		if ((coord == "g1" && _visualInfo.droppedSrc == "e1") \
			|| (coord == "g8" && _visualInfo.droppedSrc == "e8"))
			input[3] = 'O', input[4] = '-', input += "O";
		if ((coord == "c1" && _visualInfo.droppedSrc == "e1") \
			|| (coord == "c8" && _visualInfo.droppedSrc == "e8"))
			input[3] = 'O', input[4] = '-', input += + "O-O";
	}

	_visualInfo.droppedSrc.clear();
	_visualInfo.clickSrc.clear();
	_visualInfo.droppedDest.clear();

	return (input);
}

std::string	VisualGame::getKingCoords(const std::string& color) const
{
	std::string	coords;

	for (int i = 0; i != 8; i++)
	{
		for (int k = 0; k != 8; k++)
		{
			coords = { "hgfedcba"[k], "87654321"[i] };
			if (_board->getType(coords) == 'K' && _board->getColor(coords) == color)
				return (coords);
		}
	}

	return (coords);
}

std::string	VisualGame::getTurnColor(void) const
{
	if (_visualInfo.turn % 2 == 0)
		return ("white");

	return ("black");
}

bool	VisualGame::isPromotion(const std::string& coord) const
{
	if (_board->getType(_visualInfo.droppedSrc) == 'P')
	{
		if ((coord[1] == '8' && _visualInfo.droppedSrc[1] == '7') \
			|| (coord[1] == '1' && _visualInfo.droppedSrc[1] == '2'))
		{
			if (coord[0] == _visualInfo.droppedSrc[0] && _board->getType(coord) == ' ')
				return (true);
			if (coord[0] != _visualInfo.droppedSrc[0] \
				&& (coord[0] - _visualInfo.droppedSrc[0] != 1 \
				|| coord[0] - _visualInfo.droppedSrc[0] != -1) && _board->getType(coord) != ' ')
				return (true);
		}
	}

	return (false);
}

bool	VisualGame::isAbovePromotion(const int x, const int y, SDL_Rect& obj) const
{
	if (x > obj.x && x < obj.x + 20 \
		&& y > obj.y + 20 && y <= obj.y + 20 + 40)
		return (true);

	if (x > obj.x + 88 && x < (obj.x + obj.w) \
		&& y > obj.y + 20 && y <= obj.y + 20 + 40)
		return (true);

	if (x > obj.x + 32 && x < (obj.x + obj.w) - 32 \
		&& y > obj.y + 50 && y < (obj.y + obj.h))
		return (true);

	return (false);
}

bool	VisualGame::isCodeDetected(void) const
{
	if (_visualInfo.keyHistory.size() == 11)
	{
		std::vector<SDL_Keycode> code = {SDLK_UP, SDLK_UP, SDLK_DOWN, SDLK_DOWN, SDLK_LEFT, \
			SDLK_RIGHT, SDLK_LEFT, SDLK_RIGHT, SDLK_b, SDLK_a, SDLK_RETURN};

		std::vector<SDL_Keycode> sequence;
		for (size_t i = _visualInfo.keyHistory.size() - 11; i != _visualInfo.keyHistory.size(); i++)
			sequence.push_back(_visualInfo.keyHistory.at(i));

		if (code == sequence)
			return (true);
	}

	return (false);
}

bool	VisualGame::isBoardZone(const int x, const int y) const
{
	if (x >= 100 && x <= 750 && y >= 75 && y <= 725)
		return (true);

	return (false);
}

bool	VisualGame::isBoardTargetZone(const std::string& coord, const int x, const int y) const
{
	if (_board->getType(coord) != ' ' && _board->getColor(coord) == getTurnColor())
		return (true);

	if (x >= 777 && x <= _width && y >= 724 && y <= _height)
		return (true);

	if (x >= 26 && x <= 54 && y >= 725 && y <= 752)
		return (true);

	if (x > 780 && y < 60)
		return (true);

	return (false);
}


bool	VisualGame::isColorTargetZone(const int x, const int y) const
{
	if (x >= 777 && x <= _width && y >= 724 && y <= _height)
		return (true);

	return (false);
}

bool	VisualGame::isEvaluationTargetZone(const int x, const int y) const
{
	if (x >= 26 && x <= 54 && y >= 725 && y <= 752)
		return (true);

	return (false);
}
