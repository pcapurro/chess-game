#include "../chessBoard.hpp"

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

vector<string>  chessBoard::getAvailaibleMoves(void)
{
    vector<string>  legalMoves;
    vector<string>  availaibleMoves;

    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            string coord = "abcdefgh"[i] + to_string(k + 1);
            if (_board.at(getAtValue(coord)).piece != NULL && _board.at(getAtValue(coord)).piece->getColor() == _color)
            {
                availaibleMoves = getPossibleMoves(coord);
                for (int j = 0; j != availaibleMoves.size(); j++)
                    legalMoves.push_back(_board.at(getAtValue(coord)).piece->getType() + availaibleMoves.at(j));
                availaibleMoves.clear();
            }
        }
    }
    return (legalMoves);
}

char    chessBoard::getType(const string coord) const
{
    int     atValue;
    char    type;

    atValue = getAtValue(coord);
    type = ' ';
    if (coord != "none")
    {
        if (_board.at(atValue).piece != NULL)
            type = _board.at(atValue).piece->getType();
    }
    return (type);
}

string  chessBoard::getColor(const string coord) const
{
    int     atValue;
    string  color;

    atValue = getAtValue(coord);
    color = "none";
    if (coord != "none")
    {
        if (_board.at(atValue).piece != NULL)
            color = _board.at(atValue).piece->getColor();
    }
    return (color);
}

int chessBoard::getStateValue(void) const
{
    if (_checkmate == true)
        return (1);
    if (_draw == true || isAllocated() == false)
        return (2);
    return (0);
}
