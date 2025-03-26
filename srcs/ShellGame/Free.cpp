#include "ShellGame/ShellGame.hpp"

ShellGame::~ShellGame(void)
{
	if (_board != nullptr)
		delete _board, _board = nullptr;
	if (_ai != nullptr)
		delete _ai, _ai = nullptr;
}
