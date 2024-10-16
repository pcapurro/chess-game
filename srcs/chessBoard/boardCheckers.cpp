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

bool    chessBoard::isThereSomething(const string coord) const
{
    size_t  atValue;

    atValue = getAtValue(coord);
    if (_board.at(atValue).piece == NULL)
    {
        // cout << "there is nothing here..." << endl;
        return (false);
    }
    return (true);
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
    if (_board.at(atValue).piece->checkAccess(dest) != true)
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

void    chessBoard::printIllegal(void) const
{
    cout << "\033[2A" << "\033[2K";
    cerr << YELLOW << "Illegal move. " << COLOR_E;
}

bool    chessBoard::isLegal(const string move)
{
    string  src;
    string  dest;
    
    src = getSrcDestCoords(move, 0);
    dest = getSrcDestCoords(move, 1);
    
    cout << "src => " << src << endl;
    cout << "dest => " << dest << endl;
    if (isThereSomething(src) != true || isRightSide(src) != true
        || isItReachable(src, dest) != true)
    {
        printIllegal();
        _moveFailed = true;
        exit(0);
        return (false);
    }
    _moveFailed = false;
    return (true);
}
