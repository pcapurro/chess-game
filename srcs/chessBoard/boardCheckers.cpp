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

string  chessBoard::checkSource(const char type, const string src)
{
    string  source;
    string  color;

    color = _player, color[0] = tolower(color[0]);
    for (int i = 0; i != 64; i++)
    {
        if (src.find(_board.at(i).coord) != string::npos && _board.at(i).piece != NULL)
        {
            if (_board.at(i).piece->getColor() == color && _board.at(i).piece->getType() == type)
                source = source + _board.at(i).coord;
        }
    }
    if (source.length() != 2)
        source = "none";
    return (source);
}

void    chessBoard::printIllegal(void) const
{
    cout << "\033[2A" << "\033[2K";
    cerr << YELLOW << "Illegal move. " << COLOR_E;
}

bool    chessBoard::isLegal(const char obj, const string src, const string dest)
{
    string  source;

    source = checkSource(obj, src);
    if (source == "none")
    {
        printIllegal();
        _moveFailed = true;
        exit(0);
        return (false);
    }
    _moveFailed = false;
    return (true);
}
