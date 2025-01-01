#include "shellGame.hpp"

shellGame::~shellGame(void)
{
	if (_board != nullptr)
		delete _board, _board = nullptr;
	if (_ai != nullptr)
		delete _ai, _ai = nullptr;
	if (_checker != nullptr)
		delete _checker, _checker = nullptr;
}
