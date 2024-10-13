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

bool    algebraicChecker::fail() const
{
    if (_fail == false)
        return (false);
    return (true);
}

bool    algebraicChecker::isValid()
{
    if (isValidChar() != true || isGoodLength() != true)
    {
        cout << "\033[2A" << "\033[2K";
        cerr << "Try again. ";
        _fail = true;
        return (false);
    }
    _fail = false;
    return (true);
}

bool    algebraicChecker::isValidChar() const
{
    string  dictionnary;

    dictionnary = "KQRBNabcdefgh12345678+#xp0-";
    for (int i = 0; _move[i] != '\0'; i++)
    {
        if (dictionnary.find(_move[i]) > dictionnary.length())
            return (false);
    }
    return (true);
}

bool    algebraicChecker::isGoodLength() const
{
    if (_move.length() > 7 || _move.length() < 2)
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