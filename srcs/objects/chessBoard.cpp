#include "../../include/header.hpp"

chessBoard::chessBoard()
{
    _turn = 0;
    _allocated = false;
    _player = "white";

    // ...

    _allocated = true;
}

chessBoard::~chessBoard()
{
    ;
}

bool    chessBoard::isAllocated(void) const
{
    return (_allocated);
}

void    chessBoard::printBoard(void) const
{
    ;
}

bool    chessBoard::fail(void) const
{
    return (_moveFailed);
}

bool    chessBoard::isCheck() const
{
    return (true);
}

bool    chessBoard::isCheckMate() const
{
    return (false);
}

bool    chessBoard::isLegal(const string move)
{
    // if (1)
    // {
    //     cout << "\033[2A" << "\033[2K";
    //     cerr << YELLOW << "Illegal move. " << COLOR_E;
    //     _moveFailed = true;
    //     return (false);
    // }
    _moveFailed = false;
    return (true);
}

int chessBoard::getCoordinateToX(const char c) const
{
    string letters = "abcdefgh";
    for (int i = 0; letters[i] != '\0'; i++)
    {
        if (letters[i] == c)
            return (i);
    }
    return (0);
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
