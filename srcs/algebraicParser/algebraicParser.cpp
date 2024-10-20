#include "../../include/header.hpp"

algebraicParser::algebraicParser(void) { _turn = 0; }
algebraicParser::~algebraicParser(void) {;}

void    algebraicParser::operator=(const string move)
{
    _move.move = move;
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

t_move  algebraicParser::getParsedMove(void) const { return (_move); };

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
        if (isChessCoord(sequence[0]) == true && sequence[1] == '8')
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

void    algebraicParser::parseDoubleSequence(void)
{
    string  left;
    string  right;
    string  middle;

    left = getLeftSequence();
    right = getRightSequence();

    if (count(_move.move.begin(), _move.move.end(), 'x') != 0)
        _move.action = 'x';
    if (count(_move.move.begin(), _move.move.end(), '-') != 0)
        _move.action = '-';

    if (left.length() < 3 
        || (isChessCoord(_move.move[0]) == false && left.length() == 1))
    {
        vector<string>  coords;

        char c = 'i';
        if (left.length() == 1 && isChessCoord(left[0]) == true)
            c = left[0];

        if (isChessCoord(_move.move[0]) == true)
            coords = getPawnSequence(right, _turn, c);
        if (_move.move[0] == 'K')
            coords = getKingSequence(right, 'i');
        if (_move.move[0] == 'Q')
            coords = getQueenSequence(right, 'i');
        if (_move.move[0] == 'B')
            coords = getBishopSequence(right, 'i');
        if (_move.move[0] == 'N')
            coords = getKnightSequence(right, 'i');
        if (_move.move[0] == 'R')
            coords = getRookSequence(right, 'i');

        for (int i = 0; i != coords.size(); i++)
        {
            if (isChessCoord(coords.at(i)[0]) == true && isChessDigit(coords.at(i)[1]) == true)
            {
                if (left.length() != 2 || (left.length() == 2 && coords.at(i)[0] == _move.move[1]))
                    middle = middle + coords.at(i);
            }
        }
    }

    if (isChessCoord(_move.move[0]) == true && left.length() != 1)
        _move.obj = 'P', _move.src = left, _move.dest = right;
    else
    {
        isChessCoord(_move.move[0]) == true ? _move.obj = 'P' : _move.obj = _move.move[0];
        middle.size() != 0 ? _move.src = middle : _move.src = (left.c_str() + 1);
        _move.dest = right;
    }
}

void    algebraicParser::parseUniqueSequence(void)
{
    vector<string>  coords;
    int i = 0;

    if (isChessCoord(_move.move[0]) == true)
        coords = getPawnSequence(_move.move, _turn, 'i'), _move.obj = 'P';
    else
    {
        char sign = 'i';
        if (_move.move.length() == 4)
            sign = _move.move[1], i = 1;

        if (_move.move[0] == 'K')
            coords = getKingSequence(_move.move.c_str() + 1 + i, sign);
        if (_move.move[0] == 'Q')
            coords = getQueenSequence(_move.move.c_str() + 1 + i, sign);
        if (_move.move[0] == 'B')
            coords = getBishopSequence(_move.move.c_str() + 1 + i, sign);
        if (_move.move[0] == 'N')
            coords = getKnightSequence(_move.move.c_str() + 1 + i, sign);
        if (_move.move[0] == 'R')
            coords = getRookSequence(_move.move.c_str() + 1 + i, sign);
        
        _move.obj = _move.move[0];
    }

    for (int i = 0; i != coords.size(); i++)
    {
        if (isChessCoord(coords.at(i)[0]) == true && isChessDigit(coords.at(i)[1]) == true)
            _move.src = _move.src + coords.at(i);
    }
    if (isChessCoord(_move.move[0]) == true)
        _move.dest = _move.dest + _move.move.c_str();
    else
        _move.dest = _move.dest + (_move.move.c_str() + 1 + i);
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
        if (count(_move.move.begin(), _move.move.end(), '#') != 0 && count(_move.move.begin(), _move.move.end(), '#') != 1)
            return (false);
        if (count(_move.move.begin(), _move.move.end(), '+') != 0 && count(_move.move.begin(), _move.move.end(), '+') != 1)
            return (false);
        if (_move.move[_move.move.length() - 1] != '#' && _move.move[_move.move.length() - 1] != '+')
            return (false);

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

void    algebraicParser::parseMove(void)
{
    _move.src.clear();
    _move.dest.clear();

    _move.action = '>';
    if (_move.move == "O-O" || _move.move == "O-O-O")
        _move.obj = 'R', _move.src = "", _move.dest = _move.move;
    else
    {
        if (count(_move.move.begin(), _move.move.end(), '#') != 0
            || count(_move.move.begin(), _move.move.end(), '+') != 0)
            _move.move.erase(_move.move.length() - 1);

        if (count(_move.move.begin(), _move.move.end(), 'x') != 0
            || count(_move.move.begin(), _move.move.end(), '-') != 0)
            parseDoubleSequence();
        else
            parseUniqueSequence();
    }
}
