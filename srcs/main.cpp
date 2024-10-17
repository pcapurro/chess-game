#include "../include/header.hpp"

void    systemError(void)
{
    printGradually("System error. Shutting down", 2);
    exit(1);
}

void    initWelcome(void)
{
    string  input;
    printTitle();
    getline(cin, input);
    if (cin.fail() == true)
        systemError();
    cout << "\033[2A" << ERASE_LINE << endl;
}

int main(int argc, char **argv)
{
    initWelcome();
    printLoading();

    chessBoard  *board;

    board = new chessBoard;
    if (board->isAllocated() == false)
        delete board, systemError();
    else
    {
        string          input;
        algebraicParser checker;

        while (board->isCheckMate() == false && board->isAllocated() == true)
        {
            board->announceEvent(1, checker.fail(), board->fail());
            cout << ERASE_LINE << "> ";
            getline(cin, input);
        
            if (cin.fail() == true)
                systemError();
            else
            {
                checker = input;
                if (checker.fail() == true)
                    continue ;
                if (board->playMove(getParsedMove, input) == FAIL)
                    continue ;
            }
            checker.setTurn(board->getActualTurn());
            board->printBoard();
        }
        board->announceEvent(5);
        delete board;
    }
    return (0);
}
