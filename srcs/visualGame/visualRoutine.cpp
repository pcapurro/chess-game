#include "visualGame.hpp"

#include "../chessAi/chessAi.hpp"

string  visualGame::getVisualAnswer(void)
{
    string      answer;

    displayGame();
    SDL_RenderPresent(_mainRenderer);

    if (_sandBoxMode == false && _turn % 2 == _aiSide)
    {
        answer = _ai.getBestMove(_board->getHistory());
        if (answer == "error")
            return ("error");
        answer = _board->getType(string(1, answer[0]) + answer[1]) + answer;

        if (answer == "Ke1g1" || answer == "Ke8g8")
            answer = "O-O";
        if (answer == "Ke1c1" || answer == "Ke8c8")
            answer = "O-O-O";

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
        if (answer == "error")
            return (3);
        if (answer == "restart")
            return (4);

        if (answer == "end")
            { _board->printEndGame(1); return (2); }
        
        if (_board->playMove({}, answer) == FAIL)
            continue ;
        else if (_board->isAllocated() == false)
            return (1);

        if (_evaluation == true)
            _whiteScore = _board->getScore("white"), _blackScore = _board->getScore("black");

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
            { _error = true; memoryFailed(false); return ; }
        if (_board->isAllocated() == false)
            { _error = true; memoryFailed(false); return ; }

        int value = visualLoop();

        delete _board, _board = nullptr;
        if (value == 1)
            { _error = true; memoryFailed(false); return ; }
        if (value == 2)
            { return ; }
        if (value == 3)
            { _error = true; systemFailed(false); return ; }
            
        setToDefault();
        if (value != 4 && waitForNewGame() == 1)
            break ;
    }
}
