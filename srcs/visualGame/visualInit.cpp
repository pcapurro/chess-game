#include "visualGame.hpp"

visualGame::visualGame(const bool sandBoxMode) : _sandBoxMode(sandBoxMode), _width(WIDTH), _height(HEIGHT)
{
	_error = false;

	visualInfo._visualCoords = false;
	visualInfo._evaluation = true;
	visualInfo._code = true;
	visualInfo._aiSide = -1;

	_ai = nullptr;
   	if (_sandBoxMode == false)
	{
		_ai = new (nothrow) chessAi;
		if (_ai == nullptr || _ai->fail() == true)
			_error = true;
		
		srand(time(nullptr));
		visualInfo._aiSide = rand() % 2;
	}

	if (_error == false)
	{
		srand(time(nullptr));
		visualInfo._boardColor = rand() % COLOR_NB;

		setToDefault();
		setToNullPtr();

		initializeGame();

		if (_error == true)
			systemFailed(false, "SDL failed.");
		else
		{
			_textures = new (nothrow) t_textures;
			if (_textures == nullptr)
				_error = true, memoryFailed(false);

			if (_error == false)
				loadTextures();
		}
	}
}

void	visualGame::setToDefault(void)
{
	visualInfo._turn = 0;

	visualInfo._whiteScore = 0;
	visualInfo._blackScore = 0;

	visualInfo._x = 0; visualInfo._y = 0;

	visualInfo._lastMove.clear();
	visualInfo._actualCoords.clear();

	visualInfo._clickSrc.clear();
	visualInfo._droppedSrc.clear();
	visualInfo._droppedDest.clear();
}

void	visualGame::setToNullPtr(void)
{
	_board = nullptr;
	_textures = nullptr;

	_mainWindow = nullptr;
	_mainRenderer = nullptr;
	_normalCursor = nullptr;
	_playCursor = nullptr;
}

void	visualGame::initializeGame(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{ _error = true; return ; }

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	
	_mainWindow = SDL_CreateWindow("chess-game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, \
		_width, _height, 0);
	if (_mainWindow == NULL)
		{ _error = true; return ; }

	_mainRenderer = SDL_CreateRenderer(_mainWindow, -1, \
		SDL_RENDERER_ACCELERATED);
	if (_mainRenderer == NULL)
		{ _error = true; return ; }

	SDL_SetRenderDrawBlendMode(_mainRenderer, SDL_BLENDMODE_BLEND);

	_normalCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	_playCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

	if (_normalCursor == NULL || _playCursor == NULL)
		{ _error = true; return ; }
}
