#include "../includes/header.hpp"

int main(int argc, char **argv)
{
    initWelcome();
    printLoading();

    chessBoard          board;
    algebraicChecker    checker;
    string              input;

    board.announcePlayer(1);
    while (board.isCheckMate() != true)
    {
        getline(cin, input);
        if (cin.fail() == true)
        {
            cerr << "System error. Shutting down..." << endl;
            return (1);
        }
        else
        {
            checker = input;
            if (checker.isValid() != true)
                continue;
            if (board.isLegal(input) != true)
                continue;
            else
                board.playMove(input);
        }
        board.announcePlayer(1);
    }
    return (0);
}
