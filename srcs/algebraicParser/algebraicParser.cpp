#include "../../include/header.hpp"

bool    isChessDigit(const char c)
{
    if (c != '1' && c != '2' && c != '3' && c != '4'
        && c != '5' && c != '6' && c != '7' && c != '8')
        return (false);
    return (true);
}

bool    isChessPiece(const char c)
{
    if (c != 'K' && c != 'Q' && c != 'R'
        && c != 'B' && c != 'N')
        return (false);
    return (true);
}

bool    isChessCoord(const char c)
{
    if (c != 'a' && c != 'b' && c != 'c' && c != 'd'
        && c != 'e' && c != 'f' && c != 'g' && c != 'h')
        return (false);
    return (true);
}

algebraicParser::algebraicParser(void) {;}
algebraicParser::~algebraicParser(void) {;}

void    algebraicParser::operator=(const string move)
{
    _move = move;
    isValid();
    if (_fail != true)
        parseMove();
}

bool    algebraicParser::fail(void) const
{
    if (_fail == false)
        return (false);
    return (true);
}

void    algebraicParser::printInvalid(void) const
{
    cout << "\033[2A" << "\033[2K";
    cerr << RED << "Invalid move. " << COLOR_E;
}

bool    algebraicParser::isValid(void)
{
    if (isValidChar() != true || isGoodLength() != true
        || isValidSequence() != true)
    {
        printInvalid();
        _fail = true;
        return (false);
    }
    _fail = false;
    return (true);
}

bool    algebraicParser::isValidChar(void) const
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

bool    algebraicParser::isGoodLength(void) const
{
    if (_move.length() > 7 || _move.length() < 2)
        return (false);
    return (true);
}

bool    algebraicParser::isValidComplexSequence(void) const
{
    if (count(_move.begin(), _move.end(), 'x') != 0)
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
            if (isChessCoord(left[0]) != true || isChessDigit(left[1]) != true)
                return (false);
        }

        if (left.length() == 3)
        {
            if (isChessPiece(left[0]) != true || isChessCoord(left[1]) != true
                || isChessDigit(left[2]) != true)
                return (false);
        }

        if (right.length() < 2 || right.length() > 3
            || isChessCoord(right[0]) != true || isChessDigit(right[1]) != true)
            return (false);

        if (right.length() == 3 && right[1] != '8' && isChessPiece(right[2]) != true)
            return (false);
    }
    return (true);
}

bool    algebraicParser::isValidSimpleSequence(void) const
{
    if (count(_move.begin(), _move.end(), '0') != 0 || count(_move.begin(), _move.end(), '-') != 0)
    {
        if (_move != "0-0" && _move != "0-0-0")
            return (false);
        else
            return (true);
    }

    int d_count = 0, p_count = 0, l_count = 0;
    for (int i = 0; _move.c_str()[i] != '\0'; i++)
    {
        if (isChessDigit(_move[i]) == true)
            d_count++;
        if (isChessPiece(_move[i]) == true)
            p_count++;
        if (isChessCoord(_move[i]) == true)
            l_count++;
    }

    if (d_count == 0 || d_count > 2
        || p_count > 2 || l_count == 0
        || l_count > 2)
        return (false);

    if (_move.length() == 2)
    {
        if (isChessCoord(_move[0]) != true || isChessDigit(_move[1]) != true)
            return (false);
    }
    if (_move.length() == 3)
    {
        if (_move[1] == '8')
        {
            if (isChessCoord(_move[0]) != true || isChessPiece(_move[2]) != true
                || _move[2] == 'K')
                return (false);
        }
        else if (isChessDigit(_move[2]) != true || isChessCoord(_move[1]) != true
            || isChessPiece(_move[0]) != true)
            return (false);
    }
    return (true);
}

bool    algebraicParser::isValidSequence(void) const
{
    if (isValidSimpleSequence() != true || isValidComplexSequence() != true)
        return (false);
    return (true);
}

void    algebraicParser::parseMove(void)
{
    if (count(_move.begin(), _move.end(), 'x') != 0)
    {
        string  left;
        string  right;

        for (int i = 0; _move[i] != '\0'; i++)
        {
            if (_move[i] == 'x')
            {
                right = _move.c_str() + i + 1;
                break ;
            }
            if (isChessPiece(_move[i]) != true)
                left = left + _move[i];
        }
        _newMove = left + right;
    }
    else
        _newMove = _move;
}

string  algebraicParser::getParsedMove(void) const
{
    return (_newMove);
}
