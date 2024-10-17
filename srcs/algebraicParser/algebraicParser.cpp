#include "../../include/header.hpp"

algebraicParser::algebraicParser(void) { _turn = 0; }
algebraicParser::~algebraicParser(void) {;}

void    algebraicParser::operator=(const string move)
{
    _move = move;
    isValid();
    if (_fail == false)
        parseMove();
}

bool    algebraicParser::fail(void) const
{
    if (_fail == false)
        return (false);
    return (true);
}

void    algebraicParser::setTurn(const int turn) { _turn = turn; }

void    algebraicParser::printInvalid(void) const
{
    // cout << "\033[2A" << ERASE_LINE;
    cerr << RED << "Invalid move. " << COLOR_E;
}

bool    algebraicParser::isValid(void)
{
    if (isValidChar() == false || isGoodLength() == false
        || isValidSequence() == false)
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

    dictionnary = "KQRBNabcdefgh12345678xO-";
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
        if (_move[0] == 'x' || _move.at(_move.length() - 1) == 'x')
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

        if (left.length() > 3 || right.length() < 2 || right.length() > 3)
            return (false);

        if (left.length() == 1 && isChessPiece(left[0]) == true)
            return (true);

        if (left.length() == 2)
        {
            if (isChessCoord(left[0]) == true && isChessDigit(left[1]) == true)
                return (true);
            if (isChessPiece(left[0]) == true && isChessCoord(left[1]) == true)
                return (true);
        }
        if (left.length() == 3)
        {
            if (isChessPiece(left[0]) == true && isChessCoord(left[1]) == true
                && isChessDigit(left[2]) == true)
                return (true);
            if ((right[1] == '8' || right[1] == '1') && isChessPiece(right[2]) == true && right[2] != 'K'
                && isChessCoord(left[0]) == true)
                return (true);
        }
        if (isChessCoord(right[0]) == false || isChessDigit(right[1] == false)
            || (isChessPiece(right[right.length() - 1]) == true && isChessCoord(left[0]) == false))
            return (false);
    }
    return (false);
}

bool    algebraicParser::isValidSimpleSequence(void) const
{
    if (count(_move.begin(), _move.end(), 'O') != 0 || count(_move.begin(), _move.end(), '-') != 0)
    {
        if (_move == "O-O" || _move == "O-O-O")
            return (true);
    }

    if (_move.length() == 1)
        return (false);

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
        if (isChessCoord(_move[0]) == true && isChessDigit(_move[1]) == true)
            return (true);
    }
    if (_move.length() == 3)
    {
        if (isChessCoord(_move[0]) == true && _move[1] == '8')
        {
            if (isChessPiece(_move[2]) == true && _move[2] != 'K')
                return (true);
        }
        if (isChessPiece(_move[0]) == true && isChessCoord(_move[1]) == true
            && isChessDigit(_move[2]) == true)
            return (true);
    }
    if (_move.length() == 4)
    {
        if (isChessPiece(_move[0]) == true && isChessCoord(_move[1]) == true
            && isChessCoord(_move[2]) == true && isChessDigit(_move[3]) == true)
            return (true);
    }
    return (false);
}

bool    algebraicParser::isValidSequence(void) const
{
    if (isValidSimpleSequence() == true || isValidComplexSequence() == true)
        return (true);
    return (false);
}

void    algebraicParser::parseDoubleSequence(void)
{
    string  left;
    string  right;
    string  middle;

    for (int i = 0; _move[i] != '\0'; i++)
    {
        if (_move[i] == 'x')
        {
            right = _move.c_str() + i + 1;
            break ;
        }
        left = left + _move[i];
    }

    if (left.length() < 3 
        || (isChessCoord(_move[0]) == false && left.length() == 1))
    {
        vector<string>  coords;

        if (isChessCoord(_move[0]) == true)
            coords = getPawnSequence(right, _turn);
        if (_move[0] == 'K')
            coords = getKingSequence(right, 'i');
        if (_move[0] == 'Q')
            coords = getQueenSequence(right, 'i');
        if (_move[0] == 'B')
            coords = getBishopSequence(right, 'i');
        if (_move[0] == 'N')
            coords = getKnightSequence(right, 'i');
        if (_move[0] == 'R')
            coords = getRookSequence(right, 'i');

        for (int i = 0; i != coords.size(); i++)
        {
            if (isChessCoord(coords.at(i)[0]) == true && isChessDigit(coords.at(i)[1]) == true)
            {
                if (left.length() != 2 || (left.length() == 2 && coords.at(i)[0] == _move[1]))
                    middle = middle + coords.at(i);
            }
        }
    }

    if (isChessCoord(_move[0]) == true && left.length() != 1)
        _obj = 'P', _src = left, _dest = right;
    else
    {
        _obj = _move[0];
        middle.size() != 0 ? _src = middle : _src = (left.c_str() + 1);
        _dest = right;
    }
}

void    algebraicParser::parseUniqueSequence(void)
{
    vector<string>  coords;
    int i = 0;

    if (isChessCoord(_move[0]) == true)
        coords = getPawnSequence(_move, _turn), _obj = 'P';
    else
    {
        char sign = 'i';
        if (_move.length() == 4)
            sign = _move[1], i = 1;

        if (_move[0] == 'K')
            coords = getKingSequence(_move.c_str() + 1 + i, sign);
        if (_move[0] == 'Q')
            coords = getQueenSequence(_move.c_str() + 1 + i, sign);
        if (_move[0] == 'B')
            coords = getBishopSequence(_move.c_str() + 1 + i, sign);
        if (_move[0] == 'N')
            coords = getKnightSequence(_move.c_str() + 1 + i, sign);
        if (_move[0] == 'R')
            coords = getRookSequence(_move.c_str() + 1 + i, sign);
        
        _obj = _move[0];
    }

    for (int i = 0; i != coords.size(); i++)
    {
        if (isChessCoord(coords.at(i)[0]) == true && isChessDigit(coords.at(i)[1]) == true)
            _src = _src + coords.at(i);
    }
    if (isChessCoord(_move[0]) == true)
        _dest = _dest + _move.c_str();
    else
        _dest = _dest + (_move.c_str() + 1 + i);
}

void    algebraicParser::parseMove(void)
{
    _src.clear();
    _dest.clear();

    if (_move == "O-O" || _move == "O-O-O")
        _obj = 'R', _src = "", _dest = _move;
    else
    {
        if (count(_move.begin(), _move.end(), 'x') != 0)
            parseDoubleSequence();
        else
            parseUniqueSequence();
    }
    _turn++;
}

const string    algebraicParser::checkSource(void) const { return (_src); }
const string    algebraicParser::getDest(void) const { return (_dest); }
const char      algebraicParser::getObject(void) const { return (_obj); }