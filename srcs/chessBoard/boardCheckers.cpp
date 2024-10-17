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
        _src = "none";
}

void    chessBoard::printIllegal(void) const
{
    cout << "\033[2A" << ERASE_LINE;
    cerr << YELLOW << "Illegal move. " << COLOR_E;
}

bool    chessBoard::isLegal(const char obj, const string src, const string dest)
{
    checkSource(obj, src);
    // cout << src << " > " << _src << endl;
    if (_src == "none")
    {
        printIllegal();
        _moveFailed = true;
        return (false);
    }
    _moveFailed = false;
    return (true);
}
