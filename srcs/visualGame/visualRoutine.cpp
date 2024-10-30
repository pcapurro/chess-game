#include "visualGame.hpp"

int		visualGame::visualLoop(void)
{
    while (_board->isGameOver() == false)
    {
        displayGame(_board);
        if (waitForEvent(_board) == 1)
            { _board->printEndGame(1); return (2); }

        if (_board->playMove(getInput()) == FAIL)
            continue ;
        else if (_board->isAllocated() == false)
            return (1);
        setTurn();
    }
    displayGame(_board);
    _board->printEndGame(1);

    return (0);
}

void	visualGame::visualRoutine(void)
{
	if (fail() == true)
		return ;

    while (1)
    {
        _board = new (nothrow) chessBoard;
        if (!_board || _board == nullptr)
            { _error = true; memoryFailed(); return ; }
        if (_board->isAllocated() == false)
            { _error = true; memoryFailed(); return ; }

        int value = visualLoop();

        delete _board, _board = nullptr;
        if (value == 1)
            { _error = true; memoryFailed(); return ; }
        if (value == 2)
            { return ; }
            
        setToDefault();
        if (waitForNewGame() == 1)
            break ;
    }
}
