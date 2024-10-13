#include "../../includes/header.hpp"

chessBoard::chessBoard()
{
    _turn = 0;
}
chessBoard::~chessBoard()
{
    ;
}

bool    chessBoard::isCheck() const
{
    return (true);
}

bool    chessBoard::isCheckMate() const
{
    return (false);
}

bool    chessBoard::isLegal(const string move) const
{
    return (true);
}

bool    chessBoard::isValid(const string move) const
{
    return (true);
}

void    chessBoard::announcePlayer(const int value, const string move)
{
    if (_turn % 2 == 0)
        _player = "White";
    else
        _player = "Black";

    if (value == 1)
        cout << _player << " to play." << endl;
    if (value == 2)
        cout << _player << " played " << move << endl;
}

void    chessBoard::playMove(const string move)
{
    // ...
    announcePlayer(2, move);
    _turn++;
}
