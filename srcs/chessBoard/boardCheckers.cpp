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

bool    chessBoard::isThereAllyHere(const string src, const string dest) const
{
    int     atValue;
    string  destColor;
    string  srcColor;

    atValue = getAtValue(dest);
    if (_board.at(atValue).piece != NULL)
    {
        destColor = _board.at(atValue).piece->getColor();
        atValue = getAtValue(src);
        srcColor = _board.at(atValue).piece->getColor();
        if (destColor != srcColor)
            return (false);
    }
    return (true);
}

bool    chessBoard::isItReachable(const string src, const string dest) const
{
    int atValue;

    atValue = getAtValue(src);
    if (_board.at(atValue).piece->checkAccess(dest) == false)
    {
        // cout << "not reachable..." << endl;
        return (false);
    }
    return (true);
}

bool    chessBoard::isRightSide(const string src) const
{
    int     atValue;
    string  playerColor;

    atValue = getAtValue(src);
    playerColor = _player;
    playerColor[0] = tolower(playerColor[0]);
    if (_board.at(atValue).piece->getColor() != playerColor)
    {
        // cout << "bad side..." << endl;
        return (false);
    }
    return (true);
}

string  chessBoard::getSource(const char type, const string src)
{
    string  source;
    string  color;

    color = _player, color[0] = tolower(color[0]);
    for (int i = 0; i != 64; i++)
    {
        if (src.find(_board.at(i).coord) != string::npos && _board.at(i).piece != NULL)
        {
            cout << "ok" << endl;
            cout << _board.at(i).piece->getColor() << endl;
            cout << _board.at(i).piece->getType() << endl;
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
    cout << src << endl;
    cout << dest << endl;

    string  source;

    if (src.length() != 2)
        source = getSource(obj, src);

    cout << source << endl;

    exit(0);

    if (source == "none" || isRightSide(source) == false
        || isItReachable(source, dest) == false)
    {
        printIllegal();
        _moveFailed = true;
        exit(0);
        return (false);
    }
    _moveFailed = false;
    return (true);
}
