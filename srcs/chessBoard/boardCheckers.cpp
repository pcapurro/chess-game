#include "../../include/header.hpp"

bool    chessBoard::fail(void) const
{
    return (_moveFailed);
}

bool    chessBoard::isCheck(void) const
{
    return (true);
}

bool    chessBoard::isCheckMate(void) const
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
