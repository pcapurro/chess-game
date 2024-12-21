#include "shellGame.hpp"

shellGame::shellGame(const bool blindMode, const bool sandBoxMode) : _blindMode(blindMode), _sandBoxMode(sandBoxMode)
{
	_systemFail = false;
	_memoryFail = false;

	_aiSide = -1;
	srand(time(nullptr));
   	if (_sandBoxMode == false)
    {
        if (_ai.fail() == true)
            _systemFail = true;
		_aiSide = rand() % 2;
    }

	_board = nullptr;
	_checker = nullptr;

	if (_systemFail == false)
	{
		_board = new (nothrow) chessBoard;
		if (!_board || _board == nullptr)
			_memoryFail = true, memoryFailed();
		else if (_board->isAllocated() == false)
			_memoryFail = true, memoryFailed();

		_checker = new (nothrow) algebraParser;
		if (!_checker || _checker == nullptr)
			_memoryFail = true, memoryFailed();
	}
}
