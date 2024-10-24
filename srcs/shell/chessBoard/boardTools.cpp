#include "chessBoard.hpp"

size_t  chessBoard::getAtValue(const string coord) const
{
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).coord[0] == coord[0]
            && _board.at(i).coord[1] == coord[1])
            return (i);
    }
    return (0);
}

vector<string>  chessBoard::getPiecesCoords(void) const
{
    vector<string>  coords;

    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL)
            coords.push_back(_board.at(i).coord);
    }
    return (coords);
}

char    chessBoard::getType(const string coord)
{
    int     atValue;
    char    type;

    atValue = getAtValue(coord);
    type = ' ';
    if (_board.at(atValue).piece != NULL)
        type = _board.at(atValue).piece->getType();
    return (type);
}

string  chessBoard::getColor(const string coord)
{
    int     atValue;
    string  color;

    atValue = getAtValue(coord);
    color = "none";
    if (_board.at(atValue).piece != NULL)
        color = _board.at(atValue).piece->getColor();
    return (color);
}
