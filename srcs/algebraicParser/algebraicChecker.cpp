#include "../../include/header.hpp"

bool    algebraicParser::isValid(void)
{
    if (isValidChar() == false || isGoodLength() == false
        || isValidSequence() == false)
    {
        _fail = true;
        return (false);
    }
    _fail = false;
    return (true);
}

bool    algebraicParser::isValidChar(void) const
{
    string  dictionnary;

    dictionnary = "KQRBNabcdefgh12345678xO-#+";
    for (int i = 0; _move.move[i] != '\0'; i++)
    {
        if (dictionnary.find(_move.move[i]) > dictionnary.length())
            return (false);
    }
    return (true);
}

bool    algebraicParser::isGoodLength(void) const
{
    if (_move.move.length() > 7 || _move.move.length() < 2)
        return (false);
    return (true);
}

bool    algebraicParser::isValidComplexSequence(void) const
{
    if (count(_move.move.begin(), _move.move.end(), 'x') != 1
        && count(_move.move.begin(), _move.move.end(), '-') != 1)
        return (false);
    if (_move.move[0] == 'x' || _move.move.at(_move.move.length() - 1) == 'x'
        || _move.move[0] == '-' || _move.move.at(_move.move.length() - 1) == '-')
        return (false);
        
    string  left;
    string  right;

    left = getLeftSequence();
    right = getRightSequence();

    if (left.length() > 3 || right.length() < 2 || right.length() > 3)
        return (false);

    if (left.length() == 1 && isChessPiece(left[0]) == true)
        return (true);

    if (left.length() == 1 && isChessCoord(left[0]) == true)
        return (true);

    if (left.length() == 2)
    {
        if (isChessCoord(left[0]) == true && isChessDigit(left[1]) == true)
        {
            if (right[1] == '1' || right[1] == '8')
            {
                if (right.length() != 3 || isChessPiece(right[2]) == false || right[2] == 'K')
                    return (false);
            }
            return (true);
        }
        if (isChessPiece(left[0]) == true && isChessCoord(left[1]) == true)
            return (true);
    }
    if (left.length() == 3)
    {
        if (isChessPiece(left[0]) == true && isChessCoord(left[1]) == true
            && isChessDigit(left[2]) == true)
            return (true);
    }

    if (isChessCoord(right[0]) == false || isChessDigit(right[1] == false)
        || (isChessPiece(right[right.length() - 1]) == true && isChessCoord(left[0]) == false))
        return (false);
    return (false);
}

bool    algebraicParser::isValidSimpleSequence(void) const
{
    string  sequence;

    sequence = _move.move;

    if (sequence[sequence.length() - 1] == '#' || sequence[sequence.length() - 1] == '+')
        sequence.erase(sequence.length() - 1);
    
    if (_move.move.length() <= 1)
        return (false);

    int d_count = 0, p_count = 0, l_count = 0;
    for (int i = 0; sequence.c_str()[i] != '\0'; i++)
    {
        if (isChessDigit(sequence[i]) == true)
            d_count++;
        if (isChessPiece(sequence[i]) == true)
            p_count++;
        if (isChessCoord(sequence[i]) == true)
            l_count++;
    }
    if (d_count == 0 || d_count > 2
        || p_count > 2 || l_count == 0
        || l_count > 2)
        return (false);

    if (sequence.length() == 2)
    {
        if (isChessCoord(sequence[0]) == true && isChessDigit(sequence[1]) == true)
        {
            if (sequence[1] == '8' || sequence[1] == '1')
                return (false);
            return (true);
        }
    }
    if (sequence.length() == 3)
    {
        if (isChessCoord(sequence[0]) == true && (sequence[1] == '8' || sequence[1] == '1'))
        {
            if (isChessPiece(sequence[2]) == true && sequence[2] != 'K')
                return (true);
        }
        if (isChessPiece(sequence[0]) == true && isChessCoord(sequence[1]) == true
            && isChessDigit(sequence[2]) == true)
            return (true);
    }
    if (sequence.length() == 4)
    {
        if (isChessPiece(sequence[0]) == true && isChessCoord(sequence[1]) == true
            && isChessCoord(sequence[2]) == true && isChessDigit(sequence[3]) == true)
            return (true);
    }
    return (false);
}

bool    algebraicParser::isValidSequence(void) const
{
    if (count(_move.move.begin(), _move.move.end(), 'O') != 0)
    {
        if (_move.move == "O-O" || _move.move == "O-O-O")
            return (true);
    }
    else
    {
        if (count(_move.move.begin(), _move.move.end(), '#') != 0 || count(_move.move.begin(), _move.move.end(), '+') != 0)
        {
            if (count(_move.move.begin(), _move.move.end(), '#') != 0 && count(_move.move.begin(), _move.move.end(), '#') != 1)
                return (false);
            if (count(_move.move.begin(), _move.move.end(), '+') != 0 && count(_move.move.begin(), _move.move.end(), '+') != 1)
                return (false);
            if (_move.move[_move.move.length() - 1] != '#' && _move.move[_move.move.length() - 1] != '+')
                return (false);
        }

        if (count(_move.move.begin(), _move.move.end(), 'x') != 0 || count(_move.move.begin(), _move.move.end(), '-') != 0)
        {
            if (isValidComplexSequence() == true)
                return (true);
        }
        else
            if (isValidSimpleSequence() == true)
                return (true);
    }
    return (false);
}