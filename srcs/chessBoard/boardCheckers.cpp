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

bool    chessBoard::isCastlingPossible(const string move) const
{
    int atValue;

    if (_player == "White")
    {
        if (_whiteCastle != true)
            return (false);

        if (move == "O-O")
        {
            atValue = getAtValue("h1");
            if (_board.at(atValue).piece == NULL
                || _board.at(atValue).piece->getMoves() != 0)
                return (false);
            
            atValue = getAtValue("g1");
            if (_board.at(atValue).piece != NULL)
                return (false);
            atValue = getAtValue("f1");
            if (_board.at(atValue).piece != NULL)
                return (false);
        }
        if (move == "O-O-O")
        {
            atValue = getAtValue("a1");
            if (_board.at(atValue).piece == NULL
                || _board.at(atValue).piece->getMoves() != 0)
                return (false);
            
            atValue = getAtValue("b1");
            if (_board.at(atValue).piece != NULL)
                return (false);
            atValue = getAtValue("c1");
            if (_board.at(atValue).piece != NULL)
                return (false);
        }
    }
    if (_player == "Black")
    {
        if (_blackCastle != true)
            return (false);

        if (move == "O-O")
        {
            atValue = getAtValue("h8");
            if (_board.at(atValue).piece == NULL
                || _board.at(atValue).piece->getMoves() != 0)
                return (false);
            
            atValue = getAtValue("g8");
            if (_board.at(atValue).piece != NULL)
                return (false);
            atValue = getAtValue("f8");
            if (_board.at(atValue).piece != NULL)
                return (false);
        }
        if (move == "O-O-O")
        {
            atValue = getAtValue("a8");
            if (_board.at(atValue).piece == NULL
                || _board.at(atValue).piece->getMoves() != 0)
                return (false);
            
            atValue = getAtValue("b8");
            if (_board.at(atValue).piece != NULL)
                return (false);
            atValue = getAtValue("c8");
            if (_board.at(atValue).piece != NULL)
                return (false);
        }
    }
    return (true);
}

void    chessBoard::checkSource(const char type, const string src)
{
    string  color;

    _src.clear();
    color = _player, color[0] = tolower(color[0]);
    for (int i = 0; i != 64; i++)
    {
        if (src.find(_board.at(i).coord) != string::npos && _board.at(i).piece != NULL)
        {
            if (_board.at(i).piece->getColor() == color && _board.at(i).piece->getType() == type)
                _src = _src + _board.at(i).coord;
        }
    }
    if (_src.length() != 2)
    {
        printIllegal();
        _moveFailed = true;
    }
}

void    chessBoard::printIllegal(void) const
{
    cout << "\033[2A" << ERASE_LINE;
    cerr << YELLOW << "Illegal move. " << COLOR_E;
}

bool    chessBoard::isLegal(const char obj, const string src, const string dest)
{
    if (dest == "O-O-O" || dest == "O-O")
    {
        if (isCastlingPossible(dest) != true)
        {
            printIllegal();
            _moveFailed = true;
            return (false);
        }
    }
    else
        checkSource(obj, src);

    // cout << src << " > " << _src << endl << endl << endl << endl;
    // exit(0);

    return (!_moveFailed);
}
