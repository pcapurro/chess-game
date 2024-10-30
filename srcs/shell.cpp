#include "../include/shellChess.hpp"
#include "chessBoard/chessBoard.hpp"
#include "algebraParser/algebraParser.hpp"

string  getShellAnswer(const chessBoard *board, const int sandBoxMode, const int aiTurn)
{
    string  newInput;

    if (sandBoxMode == false && ((board->getActualTurn() % 2 == 0 && aiTurn % 2 == 0)
        || (board->getActualTurn() % 2 != 0 && aiTurn % 2 != 0)))
        return (getStockfishAnswer(board, aiTurn));
    else
    {
        cout << ERASE_LINE << "> ";
        getline(cin, newInput);
        cout << "\033[1A";
        if (cin.fail() == true)
            return ("error");
    }
    return (newInput);
}

int launchShellGame(void *chessBoardPtr, const bool blindMode, const bool sandBoxMode)
{
    string          input;
    chessBoard      *board;
    algebraParser   checker;
    int             aiTurn;

    aiTurn = -1;
    if (sandBoxMode == false)
        srand(time(0)), aiTurn = rand() % 2;
    if (blindMode == false)
        board->printBoard(aiTurn);

    board = (chessBoard *)chessBoardPtr;
    while (board->isGameOver() == false)
    {
        board->printEvent(checker.fail(), board->fail(), blindMode);
        input = getShellAnswer(board, sandBoxMode, aiTurn);
        if (input == "error")
            return (2);
        checker = input;

        if (checker.fail() == true || board->playMove(checker.getParsedMove()) == FAIL)
            continue ;
        else if (board->isAllocated() == false)
            return (1);

        if (blindMode == false)
            board->printBoard(aiTurn);
        checker.setTurn(board->getActualTurn());
    }
    board->printEndGame();

    return (0);
}

int initializeShellGame(const bool blindMode, const bool sandBoxMode)
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
