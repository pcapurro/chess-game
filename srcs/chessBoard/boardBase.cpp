#include "../../include/header.hpp"

void    chessBoard::announceEvent(const int value, const bool cfail, const bool bfail, const string move)
{
    if (_turn % 2 == 0)
        _player = "White";
    else
        _player = "Black";

    if (value == 1)
    {
        if (cfail == true || bfail == true)
            cout << _player << " to play." << endl;
        else
            cout << ERASE_LINE << _player << " to play." << endl;
    }
    if (value == 2)
    {
        if (_turn != 0)
            cout << "\033[3A";
        else
            cout << "\033[2A";
        cout << ERASE_LINE;
        cout << _player << " played " << move << endl;
    }
    if (value == 5)
    {
        cout << "\033[1A";
        cout << ERASE_LINE;
        cout << _player << " won the game! 🎉" << endl;
    }
}

void    chessBoard::printBoard(void)
{
    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            string coord = "abcdefgh"[i] + to_string(k + 1);
            if (_board.at(getAtValue(coord)).piece != NULL)
                cout << "[P] ; ";
            else
                cout << "[ ] ; ";
        }
        cout << endl;
    }
    cout << endl;
}

void    chessBoard::playMove(const char obj, const string src, const string dest, const string move)
{
    if (isLegal(obj, src, dest) != true)
        return ;
    else
    {
        movePiece(_src, dest);
        if (isChessPiece(dest.at(dest.length() - 1)) == true)
            promotePiece(dest, dest[dest.length() - 1]);
        printBoard();
        announceEvent(2, false, false, move);
        _turn++;
    }
}
