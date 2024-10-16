#include "../../include/header.hpp"

void    chessBoard::announceEvent(const int value, const bool cfail, const bool bfail, const string move)
{
    if (_turn % 2 == 0)
        _player = "White";
    else
        _player = "Black";

    if (value == 1)
    {
        if (cfail != false || bfail != false)
            cout << _player << " to play." << endl;
        else
            cout << "\033[2K" << _player << " to play." << endl;
    }
    if (value == 2)
    {
        if (_turn != 0)
            cout << "\033[3A";
        else
            cout << "\033[2A";
        cout << "\033[2K";
        cout << _player << " played " << move << endl;
    }
    if (value == 3)
    {
        cout << "\033[1A";
        cout << "\033[2K";
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

void    chessBoard::playMove(const string move)
{
    cout << "before => " << endl;
    printBoard();
    cout << endl;

    if (move.length() == 2)
        ;
    else
    {
        movePiece(string(1, move[0]) + string(1, move[1]), string(1, move[2]) + string(1, move[3]));

        cout << "after => " << endl;
        printBoard();
    }
    announceEvent(2, false, false, move);
    _turn++;

    exit(0); //
}
