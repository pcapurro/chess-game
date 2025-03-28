#include "VisualGame/VisualGame.hpp"

void	VisualGame::loadText(const int value)
{
	SDL_Rect		obj;
	std::string		color;

	_visualInfo.turn % 2 == 0 ? color = "white" : color = "black";

	obj.x = 215, obj.y = 14;
	obj.w = 392, obj.h = 51;

	if (value == 0)
	{
		if (color == "white")
			SDL_RenderCopy(_mainRenderer, _textures.texts.whiteToPlay.getTexture(), NULL, &obj);
		if (color == "black")
			SDL_RenderCopy(_mainRenderer, _textures.texts.blackToPlay.getTexture(), NULL, &obj);
	}
	if (value == 1)
	{
		if (color == "white")
			SDL_RenderCopy(_mainRenderer, _textures.texts.blackWon.getTexture(), NULL, &obj);
		if (color == "black")
			SDL_RenderCopy(_mainRenderer, _textures.texts.whiteWon.getTexture(), NULL, &obj);
	}

	if (value == 2)
		SDL_RenderCopy(_mainRenderer, _textures.texts.draw.getTexture(), NULL, &obj);
}

void	VisualGame::loadEvaluation(const int value)
{
	SDL_Rect	activObj;
	SDL_Rect	evalObj;

	activObj.x = 25, activObj.y = 724;
	activObj.w = 30, activObj.h = 30;

	evalObj.x = 35, evalObj.y = 80;
	evalObj.w = 10, evalObj.h = 640;

	if (_visualInfo.evaluation == true && value == 0)
	{
		int score;

		SDL_SetRenderDrawColor(_mainRenderer, 76, 153, 0, 255);
		SDL_RenderFillRect(_mainRenderer, &activObj);

		if (_sandBoxMode == false && _visualInfo.aiSide % 2 == 0)
		{
			SDL_SetRenderDrawColor(_mainRenderer, 0, 0, 0, 255);
			SDL_RenderFillRect(_mainRenderer, &evalObj);
			SDL_SetRenderDrawColor(_mainRenderer, 255, 255, 255, 255);
			score = _visualInfo.whiteScore;
		}
		else
		{
			SDL_SetRenderDrawColor(_mainRenderer, 255, 255, 255, 255);
			SDL_RenderFillRect(_mainRenderer, &evalObj);
			SDL_SetRenderDrawColor(_mainRenderer, 0, 0, 0, 255);
			score = _visualInfo.blackScore;
		}

		if (_visualInfo.whiteScore + _visualInfo.blackScore == 0)
			_visualInfo.whiteScore = 50, _visualInfo.blackScore = 50, score = 50;

		evalObj.h = ((score * 640) / (_visualInfo.whiteScore + _visualInfo.blackScore));
		SDL_RenderFillRect(_mainRenderer, &evalObj);
	}
	else
	{
		SDL_SetRenderDrawColor(_mainRenderer, 153, 0, 0, 255);
		SDL_RenderFillRect(_mainRenderer, &activObj);

		SDL_SetRenderDrawColor(_mainRenderer, 164, 164, 164, 255);
		SDL_RenderFillRect(_mainRenderer, &evalObj);
	}
}

void	VisualGame::loadMapColors(void)
{
	int			colors[COLOR_NB][3] = COLORS;
	SDL_Rect	obj = getRectangle("", "default");

	_visualInfo.boardColors.clear();
	_visualInfo.boardColors.push_back(colors[_visualInfo.boardColor][0]);
	_visualInfo.boardColors.push_back(colors[_visualInfo.boardColor][1]);
	_visualInfo.boardColors.push_back(colors[_visualInfo.boardColor][2]);

	obj.w = 60, obj.h = 66;
	obj.x = 790, obj.y = 734;
	SDL_SetRenderDrawColor(_mainRenderer, _visualInfo.boardColors.at(0), \
		_visualInfo.boardColors.at(1), _visualInfo.boardColors.at(2), 255);
	SDL_RenderFillRect(_mainRenderer, &obj);
}

void    VisualGame::loadScore(const std::string& color, const int y)
{
	int	score;

	VisualTexture*	numbers[10] = {&_textures.numbers.zero, \
		&_textures.numbers.one, &_textures.numbers.two, \
		&_textures.numbers.three, &_textures.numbers.four, \
		&_textures.numbers.five, &_textures.numbers.six, \
		&_textures.numbers.seven, &_textures.numbers.eight, \
		&_textures.numbers.nine};

	if (color == "white")
		score = _board->getWhiteMaterialsScore() - _board->getBlackMaterialsScore();
	if (color == "black")
		score = _board->getBlackMaterialsScore() - _board->getWhiteMaterialsScore();

	if (score < 0)
		score = 0;

	SDL_Rect obj = getRectangle("", std::string{color[0]} + "score");
	obj.y = y;

	SDL_Texture*	texture = _textures.symbols.plus.getTexture();
	SDL_RenderCopy(_mainRenderer, texture, NULL, &obj);

	_sandBoxMode == false || _visualInfo.aiSide % 2 != 0 ? obj.y-- : obj.y++;

	std::string value = std::to_string(score);
	for (int i = 0; value[i] != '\0'; i++)
	{
		for (int k = 0; k != 10; k++)
		{
			if (numbers[k]->getId() == value[i])
				texture = numbers[k]->getTexture();
		}
		obj.x += 15;

		SDL_RenderCopy(_mainRenderer, texture, NULL, &obj);
	}
}

void	VisualGame::loadCapturedComplex(std::vector<char> &captured, const std::string& color)
{
	SDL_Rect		obj;
	SDL_Texture*	texture;

	VisualTexture*	white[5] = {&_textures.whiteTextures.pawn, &_textures.whiteTextures.bishop, \
		&_textures.whiteTextures.knight, &_textures.whiteTextures.rook, &_textures.whiteTextures.queen};

	VisualTexture*	black[5] = {&_textures.blackTextures.pawn, &_textures.blackTextures.bishop, \
		&_textures.blackTextures.knight, &_textures.blackTextures.rook, &_textures.blackTextures.queen};

	if (color == "white")
		obj = getRectangle("", "wscore");
	if (color == "black")
		obj = getRectangle("", "bscore");

	obj.w = 33, obj.h = 33;
	for (size_t i = 0; i != captured.size(); i++)
	{
		for (int k = 0; k != 5; k++)
		{
			if (color == "white" && black[k]->getId() == captured.at(i))
				texture = black[k]->getTexture();
			if (color == "black" && white[k]->getId() == captured.at(i))
				texture = white[k]->getTexture();
		}

		SDL_RenderCopy(_mainRenderer, texture, NULL, &obj);

		obj.x += 10;
		if (captured.at(i) == 'R')
			obj.x += 15;
		if (captured.at(i) == 'B' || captured.at(i) == 'Q')
			obj.x += 21;
		if (captured.at(i) == 'N')
			obj.x += 5;

		if (obj.x >= 800 || i == captured.size() - 1 \
			|| (i != captured.size() - 1 && captured.at(i) != captured.at(i + 1)))
		{
			obj.x = 760;
			if (color == "white")
				_visualInfo.aiSide % 2 == 0 ? obj.y += 40 : obj.y -= 40;
			if (color == "black")
				_visualInfo.aiSide % 2 == 0 ? obj.y -= 40 : obj.y += 40;
		}
	}

	loadScore(color, obj.y);
}

void	VisualGame::loadCaptured(std::vector<char> &captured, const std::string& color)
{
	SDL_Rect		obj;
	SDL_Texture*	texture;

	VisualTexture*	white[5] = {&_textures.whiteTextures.pawn, &_textures.whiteTextures.bishop, \
		&_textures.whiteTextures.knight, &_textures.whiteTextures.rook, &_textures.whiteTextures.queen};

	VisualTexture*	black[5] = {&_textures.blackTextures.pawn, &_textures.blackTextures.bishop, \
		&_textures.blackTextures.knight, &_textures.blackTextures.rook, &_textures.blackTextures.queen};

	VisualTexture*	numbers[10] = {&_textures.numbers.zero, \
		&_textures.numbers.one, &_textures.numbers.two, \
		&_textures.numbers.three, &_textures.numbers.four, \
		&_textures.numbers.five, &_textures.numbers.six, \
		&_textures.numbers.seven, &_textures.numbers.eight, \
		&_textures.numbers.nine};

	if (color == "white")
		obj = getRectangle("", "wscore");
	if (color == "black")
		obj = getRectangle("", "bscore");

	char	object = ' ';

	for (size_t i = 0; i != captured.size(); i++)
	{
		if (object == ' ' || object != captured.at(i))
		{
			obj.w = 33, obj.h = 33;

			for (int k = 0; k != 5; k++)
			{
				if (color == "white" && black[k]->getId() == captured.at(i))
					texture = black[k]->getTexture();
				if (color == "black" && white[k]->getId() == captured.at(i))
					texture = white[k]->getTexture();
			}

			SDL_RenderCopy(_mainRenderer, texture, NULL, &obj);

			int value = count(captured.begin(), captured.end(), captured.at(i));
			std::string nb = std::to_string(value);

			obj.w = 14, obj.h = 35;
			obj.x += 20;

			for (int i = 0; nb[i] != '\0'; i++)
			{
				for (int k = 0; k != 10; k++)
				{
					if (numbers[k]->getId() == nb[i])
						texture = numbers[k]->getTexture();
				}
				obj.x += 15;
				SDL_RenderCopy(_mainRenderer, texture, NULL, &obj);
			}

			obj.x = 760;
			if (color == "white")
				_visualInfo.aiSide % 2 == 0 ? obj.y += 40 : obj.y -= 40;
			if (color == "black")
				_visualInfo.aiSide % 2 == 0 ? obj.y -= 40 : obj.y += 40;

		}
		object = captured.at(i);
	}

	loadScore(color, obj.y);
}

void	VisualGame::loadCaptures(void)
{
	std::vector<char>	whiteCaptured = _board->getWhiteCaptured();
	std::vector<char>	blackCaptured = _board->getBlackCaptured();

	whiteCaptured = getOrderedCaptured(whiteCaptured);
	blackCaptured = getOrderedCaptured(blackCaptured);

	if (whiteCaptured.size() > 0)
		loadCaptured(whiteCaptured, "white");
	if (blackCaptured.size() > 0)
		loadCaptured(blackCaptured, "black");
}

void    VisualGame::loadPath(void)
{
	SDL_Rect	obj;

	if (_visualInfo.droppedSrc != "")
	{
		obj = getRectangle(_visualInfo.droppedSrc);
		SDL_SetRenderDrawColor(_mainRenderer, 255, 255, 255, 128);
		SDL_RenderFillRect(_mainRenderer, &obj);

		SDL_SetRenderDrawColor(_mainRenderer, 0, 255, 128, 100);
		SDL_RenderFillRect(_mainRenderer, &obj);
	}

	if (_visualInfo.lastMove != "")
	{
		obj = getRectangle({_visualInfo.lastMove[0], _visualInfo.lastMove[1]});
		SDL_SetRenderDrawColor(_mainRenderer, 255, 255, 255, 128);
		SDL_RenderFillRect(_mainRenderer, &obj);

		SDL_SetRenderDrawColor(_mainRenderer, 204, 204, 0, 100);
		SDL_RenderFillRect(_mainRenderer, &obj);

		obj = getRectangle({_visualInfo.lastMove[2], _visualInfo.lastMove[3]});
		SDL_SetRenderDrawColor(_mainRenderer, 255, 255, 255, 128);
		SDL_RenderFillRect(_mainRenderer, &obj);

		SDL_SetRenderDrawColor(_mainRenderer, 204, 204, 0, 100);
		SDL_RenderFillRect(_mainRenderer, &obj);
	}
}

void	VisualGame::loadMap(void)
{
	bool			state;
	std::string		coords;
	SDL_Rect		obj;

	loadMapColors();

	obj = getRectangle("", "default");
	SDL_RenderCopy(_mainRenderer, _textures.boardTexture.getTexture(), NULL, &obj);

	state = true;
	for (int i = 0; i != 8; i++)
	{
		for (int k = 0; k != 8; k++)
		{
			coords = {"hgfedcba"[k], "87654321"[i]};

			if ((state == true && k % 2 == 0) || (state == false && k % 2 != 0))
			{
				obj = getRectangle(coords);
				SDL_SetRenderDrawColor(_mainRenderer, _visualInfo.boardColors.at(0), \
					_visualInfo.boardColors.at(1), _visualInfo.boardColors.at(2), 255);
				SDL_RenderFillRect(_mainRenderer, &obj);
			}
		}
		state = !state;
	}
}

void	VisualGame::loadHints(void)
{
	bool			state;
	std::string		coords;
	SDL_Rect		obj;

	SDL_SetRenderDrawColor(_mainRenderer, 0, 0, 0, 255);

	state = true;
	for (int i = 0; i != 8; i++)
	{
		for (int k = 0; k != 8; k++)
		{
			coords = {"hgfedcba"[k], "87654321"[i]};

			if (find(_visualInfo.droppedDests.begin(), _visualInfo.droppedDests.end(), coords) \
				!= _visualInfo.droppedDests.end())
			{
				obj = getRectangle(coords);
				obj.x -= 3, obj.y -= 3, obj.w = 6, obj.h = 86;
				SDL_RenderFillRect(_mainRenderer, &obj);
				obj.x += 80;
				SDL_RenderFillRect(_mainRenderer, &obj);

				obj = getRectangle(coords);
				obj.x += 3, obj.y -= 3, obj.w = 74, obj.h = 6;
				SDL_RenderFillRect(_mainRenderer, &obj);
				obj.y += 80;
				SDL_RenderFillRect(_mainRenderer, &obj);
			}
		}
		state = !state;
	}
}

void	VisualGame::loadCoords(void)
{
	SDL_Rect	obj;

	VisualTexture*	letters[8] = {&_textures.letters.h, &_textures.letters.g, \
		&_textures.letters.f, &_textures.letters.e, \
		&_textures.letters.d, &_textures.letters.c, \
		&_textures.letters.b, &_textures.letters.a};

	VisualTexture*	numbers[8] = {&_textures.numbers.one, &_textures.numbers.two, \
		&_textures.numbers.three, &_textures.numbers.four, \
		&_textures.numbers.five, &_textures.numbers.six, \
		&_textures.numbers.seven, &_textures.numbers.eight};

	for (int i = 0; i != 8; i++)
	{
		std::string	coords;

		coords = {"hgfedcba"[i], '1'};
		obj = getRectangle(coords, "coordsl");
		SDL_RenderCopy(_mainRenderer, letters[i]->getTexture(), NULL, &obj);

		coords = {'h', "12345678"[i]};
		obj = getRectangle(coords, "coordsn");
		SDL_RenderCopy(_mainRenderer, numbers[i]->getTexture(), NULL, &obj);
	}

	int	x = _visualInfo.x;
	int y = _visualInfo.y;

	if (x >= 105 && x <= 745 && y >= 80 && y <= 720 && _visualInfo.visualCoords == true \
		&& _visualInfo.actualCoords != "none" && _visualInfo.actualCoords != "" \
		&& (_sandBoxMode == true || ((_visualInfo.aiSide % 2 == 0 && _visualInfo.turn % 2 != 0) \
			|| (_visualInfo.aiSide % 2 != 0 && _visualInfo.turn % 2 == 0))))
	{
		SDL_Texture*	texture;

		obj.w = 28, obj.h = 18;
		obj.x = x - 28, obj.y = y - 18;

		SDL_SetRenderDrawColor(_mainRenderer, 192, 192, 192, 255);
		SDL_RenderFillRect(_mainRenderer, &obj);

		for (int i = 0; i != 8; i++)
		{
			if (letters[i]->getId() == _visualInfo.actualCoords[0])
				texture = letters[i]->getTexture();
		}

		obj.w = 10, obj.h = 27;

		obj.x += 3, obj.y = obj.y - 5;
		SDL_RenderCopy(_mainRenderer, texture, NULL, &obj);

		for (int i = 0; i != 8; i++)
		{
			if (numbers[i]->getId() == _visualInfo.actualCoords[1])
				texture = numbers[i]->getTexture();
		}

		obj.x += 12;
		SDL_RenderCopy(_mainRenderer, texture, NULL, &obj);
	}
}

void	VisualGame::loadBoard(const std::string& color)
{
	char			objType;
	std::string		coords;
	std::string		objColor;
	SDL_Rect		obj;

	obj.w = 80, obj.h = 80;
	obj.x = 0, obj.y = 0;

	for (int i = 0; i != 8; i++)
	{
		for (int k = 0; k != 8; k++)
		{
			coords = {"hgfedcba"[k], "87654321"[i]};
			objType = _board->getType(coords);
			objColor = _board->getColor(coords);

			if (objType != ' ' && objColor == color && coords != _visualInfo.droppedDest)
			{
				if ((coords == _visualInfo.droppedSrc && isBoardZone(_visualInfo.x, _visualInfo.y) == false
					&& _visualInfo.promotion == false) || coords != _visualInfo.droppedSrc)
				{
					obj = getRectangle(coords);
					if (obj.x > 0 && obj.y > 0 && obj.x < _width && obj.y < _height)
						SDL_RenderCopy(_mainRenderer, getTexture(objType, objColor), NULL, &obj);
				}
			}
		}
	}

	if (isBoardZone(_visualInfo.x, _visualInfo.y) == true)
	{
		objType = _board->getType(_visualInfo.droppedSrc);
		objColor = _board->getColor(_visualInfo.droppedSrc);

		obj.x = _visualInfo.x - 28, obj.y = _visualInfo.y - 40;
		SDL_RenderCopy(_mainRenderer, getTexture(objType, objColor), NULL, &obj);
	}

}

void	VisualGame::loadCheck(void)
{
	std::string		color;
	SDL_Rect		obj;

	_visualInfo.turn % 2 == 0 ? color = "white" : color = "black";
	obj = getRectangle(getKingCoords(color));

	SDL_SetRenderDrawColor(_mainRenderer, 242, 255, 0, 255);
	SDL_RenderFillRect(_mainRenderer, &obj);
}

void	VisualGame::loadDraw(void)
{
	std::string		color;
	SDL_Rect		obj;

	_visualInfo.turn % 2 == 0 ? color = "white" : color = "black";
	obj = getRectangle(getKingCoords(color));

	SDL_SetRenderDrawColor(_mainRenderer, 128, 128, 128, 255);
	SDL_RenderFillRect(_mainRenderer, &obj);

	_visualInfo.turn % 2 == 0 ? color = "black" : color = "white";
	obj = getRectangle(getKingCoords(color));

	SDL_SetRenderDrawColor(_mainRenderer, 128, 128, 128, 255);
	SDL_RenderFillRect(_mainRenderer, &obj);
}

void	VisualGame::loadCheckMate(void)
{
	std::string		color;
	std::string		kingCoords;
	SDL_Rect		obj;

	_visualInfo.turn % 2 == 0 ? color = "white" : color = "black";
	kingCoords = getKingCoords(color);
	obj = getRectangle(getKingCoords(color));

	SDL_SetRenderDrawColor(_mainRenderer, 215, 0, 21, 255);
	SDL_RenderFillRect(_mainRenderer, &obj);

	obj = getRectangle(kingCoords);
	obj.h = obj.h / 3, obj.w = obj.w / 3;
	SDL_RenderCopy(_mainRenderer, getTexture('c', color), NULL, &obj);

	color == "white" ? color = "black" : color = "white";
	kingCoords = getKingCoords(color);
	obj = getRectangle(getKingCoords(color));

	SDL_SetRenderDrawColor(_mainRenderer, 0, 190, 60, 255);
	SDL_RenderFillRect(_mainRenderer, &obj);

	obj = getRectangle(kingCoords);
	obj.h = obj.h / 3, obj.w = obj.w / 3;
	SDL_RenderCopy(_mainRenderer, getTexture('c', color), NULL, &obj);
}

void	VisualGame::displayMoveAnimation(const std::string& move)
{
	int				destX, destY;
	std::string		src, dest;
	SDL_Rect		obj;

	src = {move[0], move[1]};
	dest = {move[2], move[3]};

	obj.x = getRectangle(src).x;
	obj.y = getRectangle(src).y;

	destX = getRectangle(dest).x;
	destY = getRectangle(dest).y;

	_visualInfo.droppedSrc = src;
	while (obj.y != destY || obj.x != destX)
	{
		if ((src[0] == dest[0] && src[1] != dest[1]) || (src[0] != dest[0] && src[1] != dest[1]))
			destY > obj.y ? obj.y++ : obj.y--;
		if ((src[0] != dest[0] && src[1] == dest[1]) || (src[0] != dest[0] && src[1] != dest[1]))
			destX > obj.x ? obj.x++ : obj.x--;

		_visualInfo.x = obj.x + 28, _visualInfo.y = obj.y + 40;
		displayGame(true);
		std::this_thread::sleep_for(std::chrono::microseconds(500));
	}
}

void	VisualGame::displayPromotion(const char type, const std::string& coord)
{
	SDL_Rect		obj;
	std::string		color;

	_visualInfo.x = -1, _visualInfo.y = -1;
	displayGame();

	_visualInfo.turn % 2 == 0 ? color = "white" : color = "black";

	obj = getRectangle(coord);
	SDL_RenderCopy(_mainRenderer, getTexture(type, color), NULL, &obj);

	obj = getRectangle(coord, "promotion");
	SDL_RenderCopy(_mainRenderer, _textures.promotion.getTexture(), NULL, &obj);

	SDL_RenderPresent(_mainRenderer);
}

void	VisualGame::displayGame(const bool value)
{
	SDL_RenderClear(_mainRenderer);

	loadEvaluation(_board->getStateValue());

	loadMap();
	loadPath();

	if (_visualInfo.visualDests == true \
		&& _visualInfo.droppedDests.size() != 0)
		loadHints();

	loadCaptures();

	if (_board->isItCheckMate() == true)
		loadCheckMate();
	else if (_board->isItCheck() == true)
		loadCheck();
	else if (_board->isItDraw() == true)
		loadDraw();

	if (_visualInfo.turn % 2 == 0)
		loadBoard("black"), loadBoard("white");
	else
		loadBoard("white"), loadBoard("black");

	if (_board->getStateValue() == 0)
		loadCoords();

	loadText(_board->getStateValue());

	if (value == true)
		SDL_RenderPresent(_mainRenderer);
}
