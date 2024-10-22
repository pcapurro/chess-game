#include "../../include/header.hpp"

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
