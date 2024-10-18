#include "../../include/header.hpp"

string  chessBoard::getQueenPath(const string src, const string dest)
{
    string  coords;

    coords = getRookPath(src, dest);
    coords = coords + getBishopPath(src, dest);
    return (coords);
}

string  chessBoard::getRookPath(const string src, const string dest)
{
    int src_x = src[0] - 97;
    int src_y = atoi(src.c_str() + 1);
    
    int dest_x = dest[0] - 97;
    int dest_y = atoi(dest.c_str() + 1);

    string  coords;
    string  newCoords;

    for (int i = 0; i != 8; i++)
    {
        if (src_x > dest_x && src_y == dest_y)
            src_x--;
        if (src_x < dest_x && src_y == dest_y)
            src_x++;
        if (src_x == dest_x && src_y < dest_y)
            src_y++;
        if (src_x == dest_x && src_y > dest_y)
            src_y--;

        newCoords = newCoords + "abcdefgh"[src_x] + to_string(src_y);
        if (isChessCoord(newCoords[0]) == true && isChessDigit(newCoords[1]) == true)
            coords = coords + newCoords;
        if (isThereSomething(newCoords) == true || newCoords == dest)
            break ;
        newCoords.clear();
    }
    return (coords);
}

string  chessBoard::getBishopPath(const string src, const string dest)
{
    int src_x = src[0] - 97;
    int src_y = atoi(src.c_str() + 1);
    
    int dest_x = dest[0] - 97;
    int dest_y = atoi(dest.c_str() + 1);

    string  coords;
    string  newCoords;

    for (int i = 0; i != 8; i++)
    {
        if (src_x < dest_x && src_y < dest_y)
            src_x++, src_y++;
        if (src_x > dest_x && src_y < dest_y)
            src_x--, src_y++;
        if (src_x > dest_x && src_y > dest_y)
            src_x--, src_y--;
        if (src_x < dest_x && src_y > dest_y)
            src_x++, src_y--;

        newCoords = newCoords + "abcdefgh"[src_x] + to_string(src_y);
        if (isChessCoord(newCoords[0]) == true && isChessDigit(newCoords[1]) == true)
            coords = coords + newCoords;
        if (isThereSomething(newCoords) == true || newCoords == dest)
            break ;
        newCoords.clear();
    }
    return (coords);
}

bool    chessBoard::isTheWayClear(const char type, const string src, const string dest)
{
    if (type == 'B' || type == 'R' || type == 'Q')
    {
        string  coords;

        if (type == 'B')
            coords = getBishopPath(src, dest);
        if (type == 'R')
            coords = getRookPath(src, dest);
        if (type == 'Q')
            coords = getQueenPath(src, dest);
        
        if (coords.find(dest) == string::npos)
            return (false);
    }
    return (true);
}

bool    chessBoard::isTheDestinationSafe(const string dest)
{
    for (int i = 0; i != 64; i++)
    {
        if (_board.at(i).piece != NULL && _board.at(i).piece->getColor() != _color)
        {
            if (isTheWayClear(_board.at(i).piece->getType(), _board.at(i).coord, dest) == true)
                return (false);
        }
    }
    return (true);
}
