#include "visualGame.hpp"

#include "../chessAi/chessAi.hpp"

string  visualGame::getVisualAnswer(void)
{
    string      answer;
    chessAi     ai(_board);

    displayGame();
    SDL_RenderPresent(_mainRenderer);
    if (_sandBoxMode == false && _turn % 2 == _aiSide)
    {
        answer = ai.getNextMove();
        _lastAiMove = answer;

        if (_lastAiMove.find('O') == string::npos)
            displayMoveAnimation(_lastAiMove.c_str() + 1);
    }
    else
        answer = waitForEvent(), _lastAiMove.clear();

    return (answer);
}

int		visualGame::visualLoop(void)
{
    string  answer;

    while (_board->isGameOver() == false)
    {
        answer = getVisualAnswer();
        if (answer == "end")
            { _board->printEndGame(1); return (2); }

        if (answer == "error" || _board->playMove({}, answer) == FAIL)
            continue ;
        else if (_board->isAllocated() == false)
            return (1);
        _turn++;
    }
    displayGame();
    SDL_RenderPresent(_mainRenderer);

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
