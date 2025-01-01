#include "visualGame.hpp"

SDL_Texture	*visualGame::getTexture(const char type, const string color) const
{
	visualTexture	*whiteTextures[7] = {&_textures->symbols.checkMateBlack, &_textures->whiteTextures.king, \
		&_textures->whiteTextures.queen, &_textures->whiteTextures.rook, &_textures->whiteTextures.bishop, \
		&_textures->whiteTextures.knight, &_textures->whiteTextures.pawn};

	visualTexture	*blackTextures[7] = {&_textures->symbols.checkMateWhite, &_textures->blackTextures.king, \
		&_textures->blackTextures.queen, &_textures->blackTextures.rook, &_textures->blackTextures.bishop, \
		&_textures->blackTextures.knight, &_textures->blackTextures.pawn};

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

SDL_Rect	visualGame::getRectangle(const string coords, const string type) const
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
			_aiSide % 2 == 0 ? obj.y = 72 : obj.y = 692;
		if (type == "bscore")
			_aiSide % 2 == 0 ? obj.y = 692 : obj.y = 72;

		return (obj);
	}

	int	x = coords[0] - 97;
	int	y = atoi(coords.c_str() + 1) - 1;

	_aiSide != 0 ? y = 8 - (y + 1) : x = 7 - x;

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

vector<char>	visualGame::getOrderedCaptured(const vector<char> &captured) const
{
	vector<char>	newCaptured;

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

string	visualGame::getCoord(const int x, const int y) const
{
	int	xZone;
	int	yZone;

	if (x >= 105 && x <= 745 && y >= 80 && y <= 720)
	{
		for (int i = 0; i != 8; i++)
		{
			_aiSide == 0 ? yZone = 80 * (i + 1) : yZone = 80 * (8 - i);

			for (int k = 0; k != 8; k++)
			{
				_aiSide == 0 ? xZone = 80 * (8 - k) : xZone = 80 * (k + 1);

				if (x >= xZone && x <= xZone + 105 && y >= yZone && y <= yZone + 80)
					return (string{ "abcdefgh"[k], "12345678"[i] });
			}
		}
	}

	return ("none");
}

string	visualGame::getInput(const string coord)
{
	string	input;

	if (coord == "end" || coord == "none" || coord == "error")
		return (coord);

	input += _board->getType(_droppedSrc);
	input += _droppedSrc + coord;

	if (input[0] == 'K')
	{
		if ((coord == "g1" && _droppedSrc == "e1") || (coord == "g8" && _droppedSrc == "e8"))
			input[3] = 'O', input[4] = '-', input += "O";
		if ((coord == "c1" && _droppedSrc == "e1") || (coord == "c8" && _droppedSrc == "e8"))
			input[3] = 'O', input[4] = '-', input += + "O-O";
	}

	_droppedSrc.clear();
	_clickSrc.clear();
	_droppedDest.clear();

	return (input);
}

string	visualGame::getKingCoords(const string color) const
{
	string	coords;

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

string	visualGame::getTurnColor(void) const
{
	if (_turn % 2 == 0)
		return ("white");

	return ("black");
}

bool	visualGame::isPromotion(const string coord) const
{
	if (_board->getType(_droppedSrc) == 'P')
	{
		if ((coord[1] == '8' && _droppedSrc[1] == '7')
			|| (coord[1] == '1' && _droppedSrc[1] == '2'))
		{
			if (coord[0] == _droppedSrc[0] && _board->getType(coord) == ' ')
				return (true);
			if (coord[0] != _droppedSrc[0] && (coord[0] - _droppedSrc[0] != 1 || coord[0] - _droppedSrc[0] != -1)
				&& _board->getType(coord) != ' ')
				return (true);
		}
	}

	return (false);
}

bool	visualGame::isAbovePromotion(const int x, const int y, SDL_Rect obj) const
{
	if (x > obj.x && x < obj.x + 20
		&& y > obj.y + 20 && y <= obj.y + 20 + 40)
		return (true);

	if (x > obj.x + 88 && x < (obj.x + obj.w)
		&& y > obj.y + 20 && y <= obj.y + 20 + 40)
		return (true);

	if (x > obj.x + 32 && x < (obj.x + obj.w) - 32
		&& y > obj.y + 50 && y < (obj.y + obj.h))
		return (true);

	return (false);
}

bool	visualGame::isCodeDetected(void) const
{
	if (_keyHistory.size() == 11)
	{
		vector<SDL_Keycode> code = {SDLK_UP, SDLK_UP, SDLK_DOWN, SDLK_DOWN, SDLK_LEFT, \
			SDLK_RIGHT, SDLK_LEFT, SDLK_RIGHT, SDLK_b, SDLK_a, SDLK_RETURN};

		vector<SDL_Keycode> sequence;
		for (size_t i = _keyHistory.size() - 11; i != _keyHistory.size(); i++)
			sequence.push_back(_keyHistory.at(i));

		if (code == sequence)
			return (true);
	}

	return (false);
}

bool	visualGame::isBoardTargetZone(const string coord, const int x, const int y) const
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

bool	visualGame::isColorTargetZone(const int x, const int y) const
{
	if (x >= 777 && x <= _width && y >= 724 && y <= _height)
		return (true);

	return (false);
}

bool	visualGame::isEvaluationTargetZone(const int x, const int y) const
{
	if (x >= 26 && x <= 54 && y >= 725 && y <= 752)
		return (true);

	return (false);
}
