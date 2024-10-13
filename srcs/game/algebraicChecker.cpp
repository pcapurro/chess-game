#include "../../includes/header.hpp"

algebraicChecker::algebraicChecker()
{
    ;
}
algebraicChecker::~algebraicChecker()
{
    ;
}

void    algebraicChecker::operator=(string move)
{
    this->_move = move;
}

bool    algebraicChecker::isValid() const
{
    return (true);
}

bool    algebraicChecker::isValidChar() const
{
    for (int i = 0; this->_move[i] != '\0'; i++)
    {
        if (this->_move[i])
            ;
    }
    return (true);
}

bool    algebraicChecker::isGoodLength() const
{
    if (this->_move.length() > 7)
        return (false);
    return (true);
}

// K, Q, R, B, N
// a, b, c, d, e, f, g, h
// 1 2 3 4 5 6 7 8

// +
// #
// x
// e.p.
// 0-0
// 0-0-0

// f7xe8Q+
// Kf6xe4+
// e4
// e4xe5
// d2-d4
// Kg8-f6