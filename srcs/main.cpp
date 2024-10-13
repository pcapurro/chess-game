#include "../includes/header.hpp"

int main(int argc, char **argv)
{
    initWelcome();

    chessBoard          board;
    algebraicChecker    checker;
    string              input;

    printLoading();
    while (board.isCheckMate() != true)
    {
        getline(cin, input);
        if (cin.fail() == true)
            exit(1);
        else
        {
            checker = input;
            if (checker.isValid() != true)
                ;
            else if (board.isLegal(input) != true)
                ;
            else
                board.playMove(input);
        }
    }
    return (0);
}
