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

vector<string>  chessBoard::getLegalMoves(void)
{
    char            type;
    string          move;
    vector<string>  possibleMoves;
    vector<string>  legalMoves;
    vector<string>  availaibleTargets;

    possibleMoves.push_back("O-O");
    possibleMoves.push_back("O-O-O");

    for (int i = 0; i != 8; i++)
    {
        for (int k = 0; k != 8; k++)
        {
            string coord = "abcdefgh"[i] + to_string(k + 1);
            if (_board.at(getAtValue(coord)).piece != NULL 
                && _board.at(getAtValue(coord)).piece->getColor() == _gameInfo._color)
            {
                availaibleTargets = getPossibleTargets(coord);
                for (int j = 0; j != availaibleTargets.size(); j++)
                {
                    type = _board.at(getAtValue(coord)).piece->getType();
                    move = string(1, type) + availaibleTargets.at(j);
                    
                    if ((move.at(move.length() - 1) == '8' || move.at(move.length() - 1) == '1') && type == 'P')
                        possibleMoves.push_back(move + 'Q'), possibleMoves.push_back(move + 'B'), \
                        possibleMoves.push_back(move + 'N'), possibleMoves.push_back(move + 'R');
                    else
                        possibleMoves.push_back(move);
                }
                availaibleTargets.clear();
            }
        }
    }

    cout << "legal moves :" << endl;
    for (int i = 0; i != possibleMoves.size(); i++)
    {
        if (isLegal(possibleMoves.at(i)) == true)
            legalMoves.push_back(possibleMoves.at(i)), cout << possibleMoves.at(i) << " ; ";
    }
    cout << endl;

    return (legalMoves);
}

vector<string>  chessBoard::getCastlingSrcsDests(const string srcdest)
{
    char            y;
    string          src;
    string          dest;
    vector<string>  srcsDests;

    _gameInfo._color == "white" ? y = '1' : y = '8';

    if (srcdest == "O-O")
    {
        src = string(1, 'e') + y, dest = string(1, 'g') + y;
        srcsDests.push_back(src + dest);
        cout << "adding " << src << dest << endl;
        src = string(1, 'h') + y, dest = string(1, 'f') + y;
        srcsDests.push_back(src + dest);
        cout << "adding " << src << dest << endl;
    }
    else
    {
        src = string(1, 'e') + y, dest = string(1, 'c') + y;
        srcsDests.push_back(src + dest);
        cout << "adding " << src << dest << endl;
        src = string(1, 'a') + y, dest = string(1, 'd') + y;
        srcsDests.push_back(src + dest);
        cout << "adding " << src << dest << endl;
    }

    cout << "pushing " << srcsDests.at(0) << " ; " << srcsDests.at(1) << endl;

    return (srcsDests);
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
    if (_gameInfo._checkmate == true)
        return (1);
    if (_gameInfo._draw == true || isAllocated() == false)
        return (2);
    return (0);
}