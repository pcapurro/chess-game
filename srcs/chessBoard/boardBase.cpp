#include "../../include/header.hpp"

int chessBoard::getCoordinateToX(const char c) const //
{
    for (int i = 0; "abcdefgh"[i] != '\0'; i++)
    {
        if ("abcdefgh"[i] == c)
            return (i);
    }
    return (0);
}

void    chessBoard::printBoard(void) const //
{
    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
            cout << "[" << _board.at(i).coord << "]" << " ; ";
        cout << endl;
    }
    cout << endl;
}

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

void    chessBoard::playMove(const string move)
{
    int target_x = getCoordinateToX(move[0]) - 1;;
    int target_y = atoi(move.c_str() + 1) - 1;;

    if (move.length() == 2)
    {
        ;
    }
    else
    {
        ;
    }
    announceEvent(2, false, false, move);
    _turn++;
}
