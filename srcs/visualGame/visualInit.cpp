#include "visualGame.hpp"

visualGame::visualGame(const bool sandBoxMode) : _sandBoxMode(sandBoxMode), _width(800), _height(800)
{
    _error = false;

	_aiSide = -1;
    srand(time(nullptr));
   	if (_sandBoxMode == false)
    {
        if (_ai.fail() == true)
            _error = true;
		_aiSide = rand() % 2;
    }

    srand(time(nullptr));
    _boardColor = rand() % COLOR_NB;

    setToDefault();
    setToNullPtr();

    initializeGame();
    if (_error == false)
        loadTextures();

    _evaluation = true;
    _code = true;
}

void    visualGame::setToDefault(void)
{
    _turn = 0;

    _whiteScore = 0;
    _blackScore = 0;

    _lastMove.clear();
    _lastAiMove.clear();

    _clickSrc.clear();
    _droppedSrc.clear();
    _droppedDest.clear();
}

void    visualGame::setToNullPtr(void)
{
    _board = nullptr;

    _mainWindow = nullptr;
    _mainRenderer = nullptr;
    _normalCursor = nullptr;
    _playCursor = nullptr;

    _boardTexture = nullptr;
    _promotion = nullptr;
    _arrow = nullptr;

    _baseSurface = nullptr;
    _baseCheck = 0;

    _whiteTextures.bishop = nullptr;
    _whiteTextures.king = nullptr;
    _whiteTextures.knight = nullptr;
    _whiteTextures.pawn = nullptr;
    _whiteTextures.queen = nullptr;
    _whiteTextures.rook = nullptr;

    _blackTextures.bishop = nullptr;
    _blackTextures.king = nullptr;
    _blackTextures.knight = nullptr;
    _blackTextures.pawn = nullptr;
    _blackTextures.queen = nullptr;
    _blackTextures.rook = nullptr;

    _letters.a = nullptr;
    _letters.b = nullptr;
    _letters.c = nullptr;
    _letters.d = nullptr;
    _letters.e = nullptr;
    _letters.f = nullptr;
    _letters.g = nullptr;
    _letters.h = nullptr;

    _numbers.one = nullptr;
    _numbers.two = nullptr;
    _numbers.three = nullptr;
    _numbers.four = nullptr;
    _numbers.five = nullptr;
    _numbers.six = nullptr;
    _numbers.seven = nullptr;
    _numbers.eight = nullptr;

    _symbols.plus = nullptr;
    _symbols.moins = nullptr;

    _symbols.checkMateWhite = nullptr;
    _symbols.checkMateBlack = nullptr;

    _texts.blackToPlay = nullptr;
    _texts.blackWon = nullptr;
    _texts.draw = nullptr;
    _texts.whiteToPlay = nullptr;
    _texts.whiteWon = nullptr;
}

void    visualGame::initializeGame(void)
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
