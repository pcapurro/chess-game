#include "shellGame.hpp"

#include "../chessAi/chessAi.hpp"

string  shellGame::getShellAnswer(void) const
{
    string  answer;

    if (_sandBoxMode == false && ((_board->getActualTurn() % 2 == 0 && _aiSide % 2 == 0)
        || (_board->getActualTurn() % 2 != 0 && _aiSide % 2 != 0)))
        { chessAi ai(_board); return (ai.getNextMove()); }
    else
    {
        cout << ERASE_LINE << "> ";
        getline(cin, answer);
        cout << "\033[1A";
        if (cin.fail() == true)
            return ("error");
    }
    return (answer);
}

void	shellGame::shellRoutine(void)
{
    string	input;
    t_move  move;

    if (_blindMode == false)
        _board->printBoard(_aiSide);

    while (_board->isGameOver() == false)
    {
        _board->printEvent(_checker->fail(), _board->fail(), _blindMode);
        input = getShellAnswer();
        if (input == "error")
            { _systemFail = true; systemFailed(); return ; }
        *_checker = input;
        move = _checker->getParsedMove();

        if (move.error == false && (_checker->fail() == true || _board->playMove(move) == FAIL))
            continue ;
        if (move.error == true || _board->isAllocated() == false)
            { _memoryFail = true; memoryFailed(); return ; }

        if (_blindMode == false)
            _board->printBoard(_aiSide);
        _checker->setTurn(_board->getActualTurn());
    }
    _board->printEndGame();
}
