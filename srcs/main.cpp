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
    cout << "\033[2A" << "\033[2K" << endl;
}

int main(int argc, char **argv)
{
    initWelcome();
    printLoading();

    chessBoard  *board;

    board = new chessBoard;
    if (board->isAllocated() != true)
        delete board, systemError();
    else
    {
        string          input;
        algebraicParser checker;

        while (board->isCheckMate() != true && board->isAllocated() == true)
        {
            board->announceEvent(1, checker.fail(), board->fail());
            cout << "\033[2K" << "> ";
            getline(cin, input);
        
            if (cin.fail() == true)
                systemError();
            else
            {
                checker = input;
                if (checker.fail() != false || board->isLegal(checker.getParsedMove()) != true)
                    continue;
                else
                    board->playMove(checker.getParsedMove());
            }
        }
        board->announceEvent(5);
        delete board;
    }
    return (0);
}
