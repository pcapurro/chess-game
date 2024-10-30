#include "../include/shellChess.hpp"
#include "chessBoard/chessBoard.hpp"
#include "algebraParser/algebraParser.hpp"

int launchShellGame(void *chessBoardPtr, const int blindMode, const int sandBoxMode)
{
    string          input;
    chessBoard      *board;
    algebraParser   checker;

    board = (chessBoard *)chessBoardPtr;
    if (blindMode == false)
        board->printBoard();
    while (board->isGameOver() == false)
    {
        board->printEvent(checker.fail(), board->fail(), blindMode);
        cout << ERASE_LINE << "> ";
        getline(cin, input);
        cout << "\033[1A";

        if (cin.fail() == true)
            return (2);
        checker = input;

        if (checker.fail() == true || board->playMove(checker.getParsedMove()) == FAIL)
            continue ;
        else if (board->isAllocated() == false)
            return (1);

        if (blindMode == false)
            board->printBoard();
        checker.setTurn(board->getActualTurn());
    }
    board->printEndGame();

    return (0);
}

int initializeShellGame(const int blindMode, const int sandBoxMode)
{
    int         value;
    chessBoard  *board;

    board = new (nothrow) chessBoard;
    if (!board || board == nullptr)
        { memoryFailed(); return (1); }
    else if (board->isAllocated() == false)
    {
        delete board;
        memoryFailed();
        return (1);
    }
    value = launchShellGame(board, blindMode, sandBoxMode);
    if (value != 0)
    {
        delete board;
        if (value == 1)
            { memoryFailed(); return (1); }
        else
            { systemFailed(); return (1); }
    }
    delete board;
    return (0);
}
