#include "shellGame.hpp"

shellGame::~shellGame(void)
{
	if (_board != nullptr)
		delete _board;
	if (_checker != nullptr)
		delete _checker;
}
