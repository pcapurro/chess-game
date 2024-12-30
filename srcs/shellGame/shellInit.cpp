#include "shellGame.hpp"

shellGame::shellGame(const bool blindMode, const bool sandBoxMode) : _blindMode(blindMode), _sandBoxMode(sandBoxMode)
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

	_board = nullptr;
	_checker = nullptr;

	if (_error == false)
	{
		_board = new (nothrow) chessBoard;
		if (!_board || _board == nullptr)
			_error = true, memoryFailed(true);
		else if (_board->isAllocated() == false)
			_error = true, memoryFailed(true);

		_checker = new (nothrow) algebraParser;
		if (!_checker || _checker == nullptr)
			_error = true, memoryFailed(true);
	}
}
