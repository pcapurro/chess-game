#include "shellGame.hpp"

string  shellGame::getShellAnswer(void) const
{
    string  answer;

    if (_sandBoxMode == false && ((_board->getActualTurn() % 2 == 0 && _aiSide % 2 == 0)
        || (_board->getActualTurn() % 2 != 0 && _aiSide % 2 != 0)))
        return (aiChess::getBestMove(_board, _aiSide));
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

    if (_blindMode == false)
        _board->printBoard(_aiSide);

    while (_board->isGameOver() == false)
    {
        _board->printEvent(_checker->fail(), _board->fail(), _blindMode);
        input = getShellAnswer();
        if (input == "error")
            { _systemFail = true; systemFailed(); return ; }
        *_checker = input;

        if (_checker->fail() == true || _board->playMove(_checker->getParsedMove()) == FAIL)
            continue ;
        else if (_board->isAllocated() == false)
            { _memoryFail = true; memoryFailed(); return ; }

        if (_blindMode == false)
            _board->printBoard(_aiSide);
        _checker->setTurn(_board->getActualTurn());
    }
    _board->printEndGame();
}
