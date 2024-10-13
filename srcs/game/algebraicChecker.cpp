#include "../../includes/header.hpp"

bool    isChessDigit(char c)
{
    if (c != '1' && c != '2' && c != '3' && c != '4'
        && c != '5' && c != '6' && c != '7' && c != '8')
        return (false);
    return (true);
}

bool    isChessPiece(char c)
{
    if (c != 'K' && c != 'Q' && c != 'R'
        && c != 'B' && c != 'N')
        return (false);
    return (true);
}

bool    isChessLetter(char c)
{
    if (c != 'a' && c != 'b' && c != 'c' && c != 'd'
        && c != 'e' && c != 'f' && c != 'g' && c != 'h')
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

bool    algebraicChecker::isValidComplexSequence() const
{
    if (_move.find('x') < _move.length())
    {
        if (count(_move.begin(), _move.end(), 'x') != 1)
            return (false);
        if (_move.find('x') == 0 || _move.find('x') == _move.length() - 1)
            return (false);
        
        string  left;
        string  right;

        for (int i = 0, c = 0; _move[i] != '\0'; i++)
        {
            if (_move[i] == 'x')
                c = 1;
            if (c == 0)
                left = left + _move[i];
            if (c == 1 && _move[i] != 'x')
                right = right + _move[i];
        }

        if (left.length() < 2 || left.length() > 3)
            return (false);

        if (left.length() == 2)
        {
            if (isChessLetter(left[0]) != true)
                return (false);
            if (isChessDigit(left[1]) != true)
                return (false);
        }

        if (left.length() == 3)
        {
            if (isChessPiece(left[0]) != true)
                return (false);
            if (isChessLetter(left[1]) != true)
                return (false);
            if (isChessDigit(left[2]) != true)
                return (false);
        }

        if (right.length() < 2 || right.length() > 3)
            return (false);

        if (isChessLetter(right[0]) != true)
            return (false);
        if (isChessDigit(right[1]) != true)
            return (false);

        if (right.length() == 3)
        {
            if (isChessPiece(right[2]) != true)
                return (false);
        }
    }
    return (true);
}

bool    algebraicChecker::isValidSimpleSequence() const
{
    if (_move.find('0') < _move.length() || _move.find('-') < _move.length())
    {
        if (_move != "0-0" && _move != "0-0-0")
            return (false);
    }

    int d_count = 0, p_count = 0, l_count = 0;
    for (int i = 0; _move.c_str()[i] != '\0'; i++)
    {
        if (isChessDigit(_move[i]) == true)
            d_count++;
        if (isChessPiece(_move[i]) == true)
            p_count++;
        if (isChessLetter(_move[i]) == true)
            l_count++;
    }

    if (d_count == 0 || d_count > 2
        || p_count > 2 || l_count == 0
        || l_count > 2)
        return (false);

    if (_move.length() == 2)
    {
        if (isChessLetter(_move[0]) != true)
            return (false);
        if (isChessDigit(_move[1]) != true)
            return (false);
    }
    if (_move.length() == 3)
    {
        if (isChessDigit(_move[2]) != true)
            return (false);
        if (isChessLetter(_move[1]) != true)
            return (false);
        if (isChessPiece(_move[0]) != true)
            return (false);
    }

    return (true);
}

bool    algebraicChecker::isValidSequence() const
{
    if (isValidSimpleSequence() != true || isValidComplexSequence() != true)
        return (false);
    return (true);
}

// K, Q, R, B, N ✅
// a, b, c, d, e, f, g, h ✅
// 1 2 3 4 5 6 7 8 ✅

// x ✅
// 0-0 ✅
// 0-0-0 ✅

// e4 ✅
// d2 ✅
// f7xe8Q ✅
// Kf6xe4 ✅
// e4xe5 ✅
// Kg8 ✅