#include "../include/shellChess.hpp"
#include "chessBoard/chessBoard.hpp"
#include "algebraParser/algebraParser.hpp"

int launchShellGame(void *chessBoardPtr, const int argc)
{
    string          input;
    chessBoard      *board;
    algebraParser   checker;

    board = (chessBoard *)chessBoardPtr;
    if (argc != 3)
        board->printBoard();
    while (board->isGameOver() == false)
    {
        board->printEvent(checker.fail(), board->fail(), argc);
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

        if (argc != 3)
            board->printBoard();
        checker.setTurn(board->getActualTurn());
    }
    board->printEndGame();

    return (0);
}

int initializeShellGame(const int argc)
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
    value = launchShellGame(board, argc);
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
