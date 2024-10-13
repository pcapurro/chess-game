#include "../includes/header.hpp"

void    systemError(void)
{
    printGradually("System error. Shutting down", 2);
    exit(1);
}

int main(int argc, char **argv)
{
    chessBoard          board;
    algebraicChecker    checker;
    string              input;

    initWelcome();
    printLoading();
    board.announcePlayer(1);
    while (board.isCheckMate() != true)
    {
        getline(cin, input);
        if (cin.fail() == true)
            systemError();
        else
        {
            checker = input;
            if (checker.isValid() != true || board.isLegal(input) != true)
                continue;
            else
                board.playMove(input);
        }
        board.announcePlayer(1);
    }
    return (0);
}
