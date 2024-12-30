#include "shellGame.hpp"

#include "../chessAi/chessAi.hpp"

string  shellGame::getShellAnswer(void) const
{
    string  answer;

    if (_sandBoxMode == false && ((_board->getActualTurn() % 2 == 0 && _aiSide % 2 == 0)
        || (_board->getActualTurn() % 2 != 0 && _aiSide % 2 != 0)))
    {
        answer = _ai->getBestMove(_board->getHistory());
        if (answer == "error")
            { systemFailed(true, "Stockfish failed."); return ("error"); }

        answer = _board->getType(string(1, answer[0]) + answer[1]) + answer;

        if (answer == "Ke1g1" || answer == "Ke8g8")
            answer = "O-O";
        if (answer == "Ke1c1" || answer == "Ke8c8")
            answer = "O-O-O";

        if (answer != "O-O" && answer != "O-O-O")
        {
            if (answer[0] != 'P')
                answer = string(1, answer[0]) + answer[1] + answer[2] + "-" + (answer.c_str() + 3);
            else
                answer = string(1, answer[1]) + answer[2] + "-" + (answer.c_str() + 3);
        }

        return (answer);
    }
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
            { _error = true; systemFailed(true, "getline() failed."); return ; }

        *_checker = input;
        move = _checker->getParsedMove();

        if (move.error == false && (_checker->fail() == true || _board->playMove(move) == FAIL))
            continue ;

        if (move.error == true || _board->isAllocated() == false)
            { _error = true; memoryFailed(true); return ; }

        if (_blindMode == false)
            _board->printBoard(_aiSide);
        _checker->setTurn(_board->getActualTurn());
    }
    _board->printEndGame();
}
