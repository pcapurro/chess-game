#include "ShellGame.hpp"

ShellGame::ShellGame(const bool blindMode, const bool sandBoxMode) : \
	_blindMode(blindMode), _sandBoxMode(sandBoxMode)
{
	_aiSide = -1;

	if (_sandBoxMode == false)
	{
		_ai.emplace();

		srand(time(nullptr));
		_aiSide = rand() % 2;
	}

	_board.emplace();
}
