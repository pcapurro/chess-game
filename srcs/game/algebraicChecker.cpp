#include "../../includes/header.hpp"

bool    isChessDigit(int nb)
{
    if (nb != '1' && nb != '2' && nb != '3' && nb != '4'
        && nb != '5' && nb != '6' && nb != '7' && nb != '8')
        return (false);
    return (true);
}

algebraicChecker::algebraicChecker() {;}
algebraicChecker::~algebraicChecker() {;}

void    algebraicChecker::operator=(string move)
{
    this->_move = move;
    isValid();
}

bool    algebraicChecker::fail() const
{
    if (_fail == false)
        return (false);
    return (true);
}

bool    algebraicChecker::isValid()
{
    if (isValidChar() != true || isGoodLength() != true
        || isValidSequence() != true)
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

    dictionnary = "KQRBNabcdefgh12345678x0-";
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

bool    algebraicChecker::isValidSequence() const
{
    if (_move.find('0') < _move.length() || _move.find('-') < _move.length())
    {
        if (_move != "0-0" && _move != "0-0-0")
            return (false);
    }
    if (_move.find('x') < _move.length())
    {
        if (count(_move.begin(), _move.end(), 'x') != 1)
            return (false);
        if (_move.find('x') == 0 || _move.find('x') == _move.length() - 1)
            return (false);
    }

    if (count_if(_move.begin(), _move.end(), isChessDigit) == 0
        || count_if(_move.begin(), _move.end(), isChessDigit) > 2)
        return (false);
    return (true);
}

// K, Q, R, B, N
// a, b, c, d, e, f, g, h
// 1 2 3 4 5 6 7 8

// x
// 0-0
// 0-0-0

// f7xe8Q
// Kf6xe4
// e4
// e4xe5
// d2
// Kg8