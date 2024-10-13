#include "../includes/header.hpp"

void    systemError(void)
{
    printGradually("System error. Shutting down", 2);
    exit(1);
}

int main(int argc, char **argv)
{
    initWelcome();
    printLoading();

    chessBoard          *board;
    algebraicChecker    checker;
    string              input;

    board = new chessBoard;
    while (board->isCheckMate() != true)
    {
        board->announceEvent(1, checker.fail());
        cout << "\033[2K" << "> ";
        getline(cin, input);
        
        if (cin.fail() == true)
            systemError();
        else
        {
            checker = input;
            if (checker.fail() != false || board->isLegal(input) != true)
                continue;
            else
                board->playMove(input);
        }
    }
    board->announceEvent(3);
    delete board;
    
    return (0);
}
