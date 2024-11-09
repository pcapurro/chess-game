#include "shellGame.hpp"

shellGame::shellGame(const bool blindMode, const bool sandBoxMode) : _blindMode(blindMode), _sandBoxMode(sandBoxMode)
{
	_systemFail = false;
	_memoryFail = false;

	_aiSide = -1;
	srand((unsigned int)((uintptr_t)this));
	if (_sandBoxMode == false)
		srand(time(0)), _aiSide = rand() % 2;

	_board = nullptr;
	_checker = nullptr;

	_board = new (nothrow) chessBoard;
	if (!_board || _board == nullptr)
		_memoryFail = true, memoryFailed();
	else if (_board->isAllocated() == false)
		_memoryFail = true, memoryFailed();

	_checker = new (nothrow) algebraParser;
	if (!_checker || _checker == nullptr)
		_memoryFail = true, memoryFailed();
}
