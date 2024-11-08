#include "visualGame.hpp"

#include "../chessAi/chessAi.hpp"

string  visualGame::getVisualAnswer(void)
{
    string  answer;

    if (_sandBoxMode == false && ((_board->getActualTurn() % 2 == 0 && _aiSide % 2 == 0)
        || (_board->getActualTurn() % 2 != 0 && _aiSide % 2 != 0)))
        return (chessAi::getNextMove(_board, _aiSide));
    else
        answer = waitForEvent();
    return (answer);
}

int		visualGame::visualLoop(void)
{
    string  answer;

    while (_board->isGameOver() == false)
    {
        displayGame();
        answer = getVisualAnswer();
        if (answer == "error" || answer == "end")
            { _board->printEndGame(1); return (2); }

        if (_board->playMove({answer, '-', answer[0], \
            (string(1, answer[1]) + answer[2]), answer.c_str() + 3, false}) == FAIL)
            continue ;
        else if (_board->isAllocated() == false)
            return (1);
        _turn++;
    }
    displayGame();
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
