#include "../includes/header.hpp"

int main(int argc, char **argv)
{
    initWelcome();

    chessBoard      board;
    algebricChecker checker;
    string          input;

    while (board.isCheckMate() != true)
    {
        checker = "21";
        if (checker.isValid() != true)
            ;
        else
            board.playMove(input);
    }
    return (0);
}
