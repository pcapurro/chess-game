#include "chessBoard/chessBoard.hpp"
#include "algebraParser/algebraParser.hpp"

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
    string          input;
    algebraParser   checker;

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

    board = new (nothrow) chessBoard;
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
        delete board;
        if (value == 1)
            return (memoryFailed());
        else
            return (systemFailed());
    }
    delete board;
    return (0);
}

int main(const int argc, const char **argv)
{
    if (argc > 2 || (argc == 2 && string(argv[1]) != "--blind"))
    {
        cerr << "Error! Invalid arguments." << endl;
        cerr << "Usage: ./shell-chess [--blind]" << endl;
        return (1);
    }
    else
    {
        initWelcome();
        printLoading();

        if (shellGame(argc) != 0)
            return (1);
    }
    return (0);
}
