#include "ShellGame/ShellGame.hpp"

ShellGame::ShellGame(const bool blindMode, const bool sandBoxMode) : _blindMode(blindMode), _sandBoxMode(sandBoxMode)
{
	_aiSide = -1;
	_ai = nullptr;
	if (_sandBoxMode == false)
	{
		_ai = new ChessAi;

		srand(time(nullptr));
		_aiSide = rand() % 2;
	}

	_board = nullptr;
	_checker = nullptr;

	_board = new ChessBoard;
	_checker = new AlgebraParser;
}
