#include "../include/header.hpp"

void    initWelcome(void)
{
    string  input;
    printTitle();
    getline(cin, input);
    if (cin.fail() == true)
        systemFailed();
    cout << "\033[2A" << ERASE_LINE << endl;
}

int shellGameLoop(chessBoard *board, const int argc)
{
    int             value;
    string          input;
    algebraicParser checker;

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

int shellGame(const int argc)
{
    int         value;
    chessBoard  *board;

    board = new (std::nothrow) chessBoard;
    if (!board || board == nullptr)
        return (1);
    else if (board->isAllocated() == false)
    {
        delete board;
        return (1);
    }
    value = shellGameLoop(board, argc);
    if (value != 0)
    {
        if (value == 1)
            memoryFailed();
        else
            systemFailed();
        delete board;
        return (1);
    }
    delete board;
    return (0);
}
