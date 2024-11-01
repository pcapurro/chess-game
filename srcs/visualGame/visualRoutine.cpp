#include "visualGame.hpp"

string  visualGame::getVisualAnswer(void)
{
    string  newInput;

    if (_sandBoxMode == false && ((_board->getActualTurn() % 2 == 0 && _aiSide % 2 == 0)
        || (_board->getActualTurn() % 2 != 0 && _aiSide % 2 != 0)))
    {
        static int i = 0;

        i++;

        if (_aiSide == 0)
        {
            if (i == 1)
            {
                _input.action = '-';
                _input.obj = 'P';
                _input.dest = "e4";
                _input.src = "e2";
            }

            if (i == 2)
            {
                _input.action = '-';
                _input.obj = 'N';
                _input.dest = "f3";
                _input.src = "g1";
            }

            if (i == 3)
            {
                _input.action = '-';
                _input.obj = 'B';
                _input.dest = "c4";
                _input.src = "f1";
            }
        }
        else
        {
            if (i == 1)
            {
                _input.action = '-';
                _input.obj = 'P';
                _input.dest = "e5";
                _input.src = "e7";
            }

            if (i == 2)
            {
                _input.action = '-';
                _input.obj = 'N';
                _input.dest = "f6";
                _input.src = "g8";
            }

            if (i == 3)
            {
                _input.action = '-';
                _input.obj = 'B';
                _input.dest = "c5";
                _input.src = "f8";
            }
        }
    }
    else
    {
        if (waitForEvent() == 1)
            return ("end");
    }
    return (newInput);
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

        if (_board->playMove(getInput()) == FAIL)
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
