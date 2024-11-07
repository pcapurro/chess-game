#include "visualGame.hpp"

visualGame::visualGame(const bool sandBoxMode) : _sandBoxMode(sandBoxMode), _width(800), _height(800)
{
    _error = false;

	_aiSide = 1;
   	// if (_sandBoxMode == false)
		// srand(time(0)), _aiSide = rand() % 2;

    setToDefault();
    setToNullPtr();

    initializeGame();
    if (_error == false)
        loadTextures();
    if (_error == false)
        loadTexts();
}

void    visualGame::setToDefault(void)
{
    _turn = 1;

    _dropped = true;
    _droppedSrc.clear();
}

void    visualGame::setToNullPtr(void)
{
    _board = nullptr;

    _mainWindow = nullptr;
    _mainRenderer = nullptr;
    _normalCursor = nullptr;
    _playCursor = nullptr;

    _whiteBoardTexture = nullptr;
    _blackBoardTexture = nullptr;
    _arrowTexture = nullptr;
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
    
    _mainWindow = SDL_CreateWindow("shell-chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, \
        _width, _height, 0);
    if (_mainWindow == NULL)
        { _error = true; return ; }

    _mainRenderer = SDL_CreateRenderer(_mainWindow, -1, \
        SDL_RENDERER_ACCELERATED);
    if (_mainRenderer == NULL)
        { _error = true; return ; }

    _normalCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    _playCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

    if (_normalCursor == NULL || _playCursor == NULL)
        { _error = true; return ; }
}
